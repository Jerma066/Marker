#ifndef GRAPHWINDOW_H
#define GRAPHWINDOW_H

#include <QMainWindow>
#include <QDebug>

#include "genereic/commontypes.h"
#include "GraphWindow/GraphObject/graphobject.h"
#include "GraphWindow/qcustomplot.h"
#include "GraphWindow/TitleDialog/titledialog.h"
#include "GraphWindow/AxisNameDialog/axisnamedialog.h"
#include "GraphWindow/AxisRangeDialog/axisrangedialog.h"

namespace Ui {
class GraphWindow;
}

class GraphWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GraphWindow(allGraphsData dt, ApproximationMethod a_m = ApproximationMethod::Linnear,
                         ErrorFunctions e_f = ErrorFunctions::MSE, QWidget *parent = nullptr);
    ~GraphWindow();

    void addNewGraph(const graphhDataFrame&,
                     const ApproximationMethod&,
                     const ErrorFunctions&);

public slots:
    void changeTitle(QString);
    void changeAxesNames(QString, QString);
    void changeAxesRanges(double, double, double, double);

private slots:
    void on_actionSet_title_of_the_graphs_triggered();
    void on_actionSet_axes_names_triggered();
    void on_actionSet_axes_ranges_triggered();
    void on_actionClear_all_plots_triggered();

private:
    QCPErrorBars* addErrorBars(const size_t& g_ind, const QCPErrorBars::ErrorType& err_type,
                               const QVector<double>& error_bars);

private:
    Ui::GraphWindow *ui;
    std::vector<QPair<GraphObject, size_t>> _graphs;
    std::vector<QCPErrorBars*> error_bars;
    QCustomPlot* customPlot;
    TitleDialog tiDialog;
    AxisNameDialog axNameDialog;
    AxisRangeDialog axRangeDialog;

    ApproximationMethod cur_approx_meth;
    ErrorFunctions cur_error_func;

    QCPTextElement* title;

};

#endif // GRAPHWINDOW_H
