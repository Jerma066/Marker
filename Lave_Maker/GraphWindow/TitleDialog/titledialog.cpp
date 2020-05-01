#include "titledialog.h"
#include "ui_titledialog.h"

TitleDialog::TitleDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TitleDialog)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("Title Dialog"));
}

TitleDialog::~TitleDialog()
{
    delete ui;
}

QString TitleDialog::getTitle()
{
    return _title;
}

void TitleDialog::on_titleOkButton_clicked()
{
    _title = ui->titleLineEdit->text();
    emit titleChanged(_title);
    this->hide();
}
