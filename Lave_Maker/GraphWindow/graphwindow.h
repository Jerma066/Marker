#ifndef GRAPHWINDOW_H
#define GRAPHWINDOW_H

#include <QMainWindow>
#include <QDebug>

#include "genereic/commontypes.h"
#include "GraphWindow/GraphObject/graphobject.h"
#include "GraphWindow/qcustomplot.h"

namespace Ui {
class GraphWindow;
}

class GraphWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GraphWindow(allGraphsData dt, QWidget *parent = nullptr);
    ~GraphWindow();

    void addNewGraph(const graphhDataFrame&);


private:
    Ui::GraphWindow *ui;
    std::vector<QPair<GraphObject, size_t>> _graphs;
    QCustomPlot* customPlot;
};

#endif // GRAPHWINDOW_H
