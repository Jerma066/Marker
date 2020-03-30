#include "filereaderdialog.h"
#include "ui_filereaderdialog.h"

FileReaderDialog::FileReaderDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileReaderDialog)
{
    ui->setupUi(this);
}

FileReaderDialog::~FileReaderDialog()
{
    delete ui;
}
