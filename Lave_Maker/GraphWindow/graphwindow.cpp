#include "graphwindow.h"
#include "GraphWindow/qcustomplot.h"
#include "ui_graphwindow.h"

GraphWindow::GraphWindow(allGraphsData dt, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GraphWindow)
{
    ui->setupUi(this);
    customPlot = ui->graphWidget;
    for(size_t i = 0; i < dt.size(); i++){
        this->addNewGraph(dt[i]);
    }
    this->show();
}

GraphWindow::~GraphWindow()
{
    delete ui;
}

void GraphWindow::addNewGraph(const graphhDataFrame& gdf)
{
    GraphObject go(gdf);
    size_t N = 10;
    double h = (go.getMax_x() - go.getMin_x())/N;
    QVector<double> x(N), y(N);
    for (size_t i = 0; i < N; ++i){
        x[i] = go.getMin_x() + i*h;
        y[i] = go._dependance(x[i]);
    }
    customPlot->addGraph();
    customPlot->graph(_graphs.size())->setData(x, y);
    customPlot->xAxis->setLabel("X coordinate");
    customPlot->yAxis->setLabel("Y coordinate");
    if(_graphs.size() == 0){
        customPlot->xAxis->setRange(go.getMin_x() - 3, go.getMax_x() + 3);
        customPlot->yAxis->setRange(*(std::min_element(y.begin(), y.end())) - 3,
                                    *(std::max_element(y.begin(), y.end())) + 3);
    }

    QVector<float> x_points(go.getPoints_values().size()), y_points(go.getPoints_values().size());
    for (int i = 0; i < x_points.size(); ++i){
        x_points[i] = go.getPoints_values()[i].x;
        y_points[i] = go.getPoints_values()[i].y;
    }

    customPlot->graph(_graphs.size())->setData(x, y);
    customPlot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 4));

    customPlot->replot();
    _graphs.push_back(qMakePair(go, _graphs.size()));
}
