#include "axisnamedialog.h"
#include "ui_axisnamedialog.h"

AxisNameDialog::AxisNameDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AxisNameDialog)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("Axes Names Dialog"));
}

AxisNameDialog::~AxisNameDialog()
{
    delete ui;
}

void AxisNameDialog::on_okNamesOfAxesButton_clicked()
{
    axesNames.first = ui->xAxNameLineEdit->text();
    axesNames.second = ui->yAxNameLineEdit->text();

    emit axesNamesChanged(axesNames.first, axesNames.second);
    this->hide();
}
