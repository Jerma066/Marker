#include "axisrangedialog.h"
#include "ui_axisrangedialog.h"

AxisRangeDialog::AxisRangeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AxisRangeDialog)
{
    ui->setupUi(this);
}

AxisRangeDialog::~AxisRangeDialog()
{
    delete ui;
}

void AxisRangeDialog::on_okAxRangeButton_clicked()
{
    x_range = qMakePair(ui->xFromLineEdit->text().toDouble(),
                        ui->xToLineEdit->text().toDouble());
    y_range = qMakePair(ui->yFromLineEdit->text().toDouble(),
                        ui->yToLineEdit->text().toDouble());

    emit axesRangesChanged(x_range.first, x_range.second,
                           y_range.first, y_range.second);
    this->hide();
}

void AxisRangeDialog::setX_range(const QPair<double, double> &range)
{
    x_range = range;
    ui->xFromLineEdit->setText(QString::number(range.first));
    ui->xToLineEdit->setText(QString::number(range.second));
}
void AxisRangeDialog::setY_range(const QPair<double, double>& range)
{
    y_range = range;
    ui->yFromLineEdit->setText(QString::number(range.first));
    ui->yToLineEdit->setText(QString::number(range.second));
}

QPair<double, double> AxisRangeDialog::getX_range()
{
    return x_range;
}

QPair<double, double> AxisRangeDialog::getY_range()
{
    return y_range;
}


