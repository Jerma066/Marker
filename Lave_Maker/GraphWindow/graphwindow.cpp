#include "graphwindow.h"
#include "GraphWindow/qcustomplot.h"
#include "ui_graphwindow.h"

GraphWindow::GraphWindow(allGraphsData dt, ApproximationMethod a_m,
                         ErrorFunctions e_f, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GraphWindow),
    tiDialog(this),
    axNameDialog(this),
    axRangeDialog(this),
    cur_approx_meth(a_m),
    cur_error_func(e_f)
{
    ui->setupUi(this);
    customPlot = ui->graphWidget;

    //Заполнение стилей линий
    line_stile.push_back(QPen(Qt::black));
    line_stile.push_back(QPen(Qt::red));
    line_stile.push_back(QPen(Qt::green));
    line_stile.push_back(QPen(Qt::blue));
    line_stile.push_back(QPen(Qt::magenta));
    line_stile.push_back(QPen(Qt::yellow));
    line_stile.push_back(QPen(Qt::gray));
    line_stile.push_back(QPen(Qt::cyan));
    line_stile.push_back(QPen(Qt::darkRed));
    line_stile.push_back(QPen(Qt::darkGreen));
    line_stile.push_back(QPen(Qt::darkBlue));
    line_stile.push_back(QPen(Qt::darkMagenta));
    line_stile.push_back(QPen(Qt::darkYellow));
    line_stile.push_back(QPen(Qt::darkGray));
    line_stile.push_back(QPen(Qt::darkCyan));
    line_stile.push_back(QPen(Qt::lightGray));

    customPlot->legend->setVisible(true);
    QFont legendFont = font();  // start out with MainWindow's font..
    legendFont.setPointSize(9); // and make a bit smaller for legend
    customPlot->legend->setFont(legendFont);
    customPlot->legend->setBrush(QBrush(QColor(255,255,255,230)));
    // By default, the legend is in the inset layout of the main axis rect.
    // So this is how we access it to change legend placement:
    customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignBottom|Qt::AlignRight);


    for(size_t i = 0; i < dt.size(); i++){
        this->addNewGraph(dt[i], a_m, e_f);
    }

    connect(&tiDialog, SIGNAL(titleChanged(QString)), this, SLOT(changeTitle(QString)));
    connect(&axNameDialog, SIGNAL(axesNamesChanged(QString, QString)), this, SLOT(changeAxesNames(QString, QString)));
    connect(&axRangeDialog, SIGNAL(axesRangesChanged(double, double, double, double)), this,
            SLOT(changeAxesRanges(double, double, double, double)));

    this->show();
}

GraphWindow::~GraphWindow()
{
    for(auto it = error_bars.begin(); it != error_bars.end(); it++){
        delete *it;
    }
    error_bars.clear();
    delete title;
    delete customPlot;
    delete ui;
}

//Каждый график - суперпозиция двух графиков: линия + точки на линии
void GraphWindow::addNewGraph(const graphhDataFrame& gdf, const ApproximationMethod& a_m,
                              const ErrorFunctions& e_f)
{
    GraphObject go(gdf, a_m, e_f);
    size_t N = 10;

    // Отрисовка линии
    double h = (go.getMax_x() - go.getMin_x())/(N*2);
    QVector<double> x(N+2), y(N+2);
    for (size_t i = 0; i < N; ++i){
        x[i] = go.getMin_x() + i*h;
        y[i] = go._dependance(x[i]);
    }
    x[N] = go.getMax_x() + h; y[N] = go._dependance(x[N]);
    x[N+1] = go.getMin_x() - h; y[N+1] = go._dependance(x[N+1]);

    customPlot->addGraph();
    customPlot->graph(_graphs.size())->setData(x, y);
    customPlot->xAxis->setLabel("X coordinate");
    customPlot->yAxis->setLabel("Y coordinate");
    if(_graphs.size() == 0){
        customPlot->xAxis->setRange(go.getMin_x() - 2, go.getMax_x() + 2);
        axRangeDialog.setX_range(qMakePair(go.getMin_x() - 2, go.getMax_x() + 2));
        customPlot->yAxis->setRange(*(std::min_element(y.begin(), y.end())) - 2,
                                    *(std::max_element(y.begin(), y.end())) + 2);
        axRangeDialog.setY_range(qMakePair(*(std::min_element(y.begin(), y.end())) - 2,
                                           *(std::max_element(y.begin(), y.end())) + 2));
    }
    else{
        QPair<double, double> new_x_r = axRangeDialog.getX_range();
        QPair<double, double> new_y_r = axRangeDialog.getY_range();
        bool x_range_changed = false;
        bool y_range_changed = false;
        if((go.getMin_x() - 2) < new_x_r.first){
            new_x_r.first = (go.getMin_x() - 2);
            x_range_changed = true;
        }
        if((go.getMax_x() + 2) > new_x_r.second){
            new_x_r.second = (go.getMax_x() + 2);
            x_range_changed = true;
        }
        if((*(std::min_element(y.begin(), y.end())) - 2) <  new_y_r.first ){
            new_y_r.first = *(std::min_element(y.begin(), y.end())) - 2;
            y_range_changed = true;
        }
        if((*(std::max_element(y.begin(), y.end())) + 2) > new_y_r.second){
            new_y_r.second = (*(std::max_element(y.begin(), y.end())) + 2);
            y_range_changed = true;
        }

        if(x_range_changed){
            customPlot->xAxis->setRange(new_x_r.first, new_x_r.second);
            axRangeDialog.setX_range(new_x_r);
        }
        if(y_range_changed){
            customPlot->yAxis->setRange(new_y_r.first, new_y_r.second);
            axRangeDialog.setY_range(new_y_r);
        }
    }

    customPlot->graph(_graphs.size())->setPen(getPen(_graphs.size()));
    customPlot->graph(_graphs.size())->setName("{Equetion: " + go.getEquation_str() + "; Error: "
                                               + QString::number(go.get_err()) + "}");
    _graphs.push_back(qMakePair(go, _graphs.size()));

    // Отрисовка точек
    QVector<double> x_points(go.getPoints_values().size()), y_points(go.getPoints_values().size());
    for (int i = 0; i < x_points.size(); ++i){
        x_points[i] = go.getPoints_values()[i].x;
        y_points[i] = go.getPoints_values()[i].y;
    }
    customPlot->addGraph();
    customPlot->graph(_graphs.size())->addData(x_points, y_points);
    customPlot->graph(_graphs.size())->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 4));
    customPlot->graph(_graphs.size())->setLineStyle(QCPGraph::lsNone);
    customPlot->legend->removeAt((_graphs.size()/2) + 1);

    // Отрисовка планок погрешностей
    QVector<double> x_error_bars;
    QVector<double> y_error_bars;

    bool we_have_error_bars = false;
    for (int i = 0; i < x_points.size(); i++){
        x_error_bars.push_back(go.getPoints_values()[i].x_error);
        y_error_bars.push_back(go.getPoints_values()[i].y_error);
        if(go.getPoints_values()[i].x_error != 0 || go.getPoints_values()[i].y_error != 0){
            we_have_error_bars = true;
        }
    }
    if(we_have_error_bars){
        addErrorBars(_graphs.size(), QCPErrorBars::ErrorType::etKeyError, x_error_bars);
        addErrorBars(_graphs.size(), QCPErrorBars::ErrorType::etValueError, y_error_bars);
    }
    else{
        QCPErrorBars* value_errorBars = new QCPErrorBars(customPlot->xAxis, customPlot->yAxis);
        value_errorBars->removeFromLegend();
        error_bars.push_back(value_errorBars);
        error_bars.push_back(value_errorBars);
    }

    _graphs.push_back(qMakePair(go, _graphs.size()));
    customPlot->replot();
}

void GraphWindow::changeTitle(QString ttl)
{
    customPlot->plotLayout()->insertRow(0);
    title = new QCPTextElement(customPlot, ttl, QFont("sans", 12, QFont::Bold));
    customPlot->plotLayout()->addElement(0, 0, title);
    customPlot->replot();
}

void GraphWindow::changeAxesNames(QString x_axis_name, QString y_axis_name)
{
    if(!x_axis_name.isEmpty()){
        customPlot->xAxis->setLabel(x_axis_name);
    }
    if(!x_axis_name.isEmpty()){
        customPlot->yAxis->setLabel(y_axis_name);
    }
    customPlot->replot();
}

void GraphWindow::changeAxesRanges(double x_from, double x_to,
                                   double y_from, double y_to)
{
    customPlot->xAxis->setRange(x_from, x_to);
    customPlot->yAxis->setRange(y_from, y_to);
    customPlot->replot();
}

void GraphWindow::on_actionSet_title_of_the_graphs_triggered()
{
    tiDialog.show();
}

void GraphWindow::on_actionSet_axes_names_triggered()
{
    axNameDialog.show();
}

void GraphWindow::on_actionSet_axes_ranges_triggered()
{
    axRangeDialog.show();
}

void GraphWindow::on_actionClear_all_plots_triggered()
{
    customPlot->clearGraphs();
    customPlot->replot();
}

QCPErrorBars* GraphWindow::addErrorBars(const size_t& g_ind, const QCPErrorBars::ErrorType& err_type,
                               const QVector<double>& err_bars)
{
    QCPErrorBars* value_errorBars = new QCPErrorBars(customPlot->xAxis, customPlot->yAxis);
    value_errorBars->removeFromLegend();
    value_errorBars->setAntialiased(false);
    value_errorBars->setErrorType(err_type);
    value_errorBars->setDataPlottable(customPlot->graph(g_ind));
    value_errorBars->setData(err_bars);

    error_bars.push_back(value_errorBars);
    return value_errorBars;
}

QPen GraphWindow::getPen(int i)
{
    // Граффик - каждое честое число. Каждое нечетное - точки
    i = abs(i/2) % line_stile.size();
    return line_stile[i];
}
void GraphWindow::on_actionGraphs_info_triggered(bool checked)
{
    if(checked){
        customPlot->legend->setVisible(true);
    }
    else{
        customPlot->legend->setVisible(false);
    }
}
