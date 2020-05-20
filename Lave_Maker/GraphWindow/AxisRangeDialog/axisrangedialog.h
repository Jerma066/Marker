#ifndef AXISRANGEDIALOG_H
#define AXISRANGEDIALOG_H

#include <QDialog>

namespace Ui {
class AxisRangeDialog;
}

class AxisRangeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AxisRangeDialog(QWidget *parent = nullptr);
    ~AxisRangeDialog();

    void setX_range(const QPair<double, double> &value);
    void setY_range(const QPair<double, double> &value);
    QPair<double, double> getX_range();
    QPair<double, double> getY_range();


signals:
    void axesRangesChanged(double, double, double, double);

private slots:
    void on_okAxRangeButton_clicked();

private:
    Ui::AxisRangeDialog *ui;
    QPair<double, double> x_range;
    QPair<double, double> y_range;
};

#endif // AXISRANGEDIALOG_H
