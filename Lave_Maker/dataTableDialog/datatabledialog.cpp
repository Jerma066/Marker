#include "datatabledialog.h"
#include "ui_datatabledialog.h"

dataTableDialog::dataTableDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dataTableDialog)
{
    ui->setupUi(this);
}

dataTableDialog::~dataTableDialog()
{
    delete ui;
}
