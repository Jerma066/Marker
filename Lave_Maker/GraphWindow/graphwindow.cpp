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
    x[N] = go.getMin_x() + (N+1)*h; y[N] = go._dependance(x[N]);
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
