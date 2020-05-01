#ifndef AXISNAMEDIALOG_H
#define AXISNAMEDIALOG_H

#include <QDialog>

namespace Ui {
class AxisNameDialog;
}

class AxisNameDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AxisNameDialog(QWidget *parent = nullptr);
    ~AxisNameDialog();

signals:
    void axesNamesChanged(QString, QString);

private slots:
    void on_okNamesOfAxesButton_clicked();

private:
    Ui::AxisNameDialog *ui;
    QPair<QString, QString> axesNames;
};

#endif // AXISNAMEDIALOG_H
