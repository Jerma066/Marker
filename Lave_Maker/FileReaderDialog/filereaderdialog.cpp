#include "filereaderdialog.h"
#include "ui_filereaderdialog.h"

#include <QDebug>

FileReaderDialog::FileReaderDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileReaderDialog)
{
    ui->setupUi(this);

    // Создание области в которую можно скидывать файл с данными
    dropArea = new DropArea;
    connect(dropArea, &DropArea::changed, this, &FileReaderDialog::getFileName);
    ui->drLayout->addWidget(dropArea);
    setWindowTitle(tr("Open data file"));
    setMinimumSize(350, 500);

    // Создание menuBar
    fileMenu = new QMenu("&File");
    fileMenu->addAction("&Open", this, SLOT(OpenFile()), Qt::CTRL + Qt::Key_O);

    menuBar = new QMenuBar(this);
    menuBar->addMenu(fileMenu);
    ui->gridLayout_2->setMenuBar(menuBar);

    this->show();
}

FileReaderDialog::~FileReaderDialog()
{
    for(auto action = menuBarActions.begin();
        action != menuBarActions.end(); action++)
    {
        delete *action;
    }
    delete fileMenu;
    delete menuBar;
    delete dropArea;
    delete ui;
}

void FileReaderDialog::OpenFile()
{
    file_path = QFileDialog::getOpenFileName(this, tr("Open Dialog"), "",
                                                   "XLSX (* .xlsx);;Text Files (*.txt)");
}

void FileReaderDialog::getFileName(const QString& path)
{
    file_path = path;
}

void FileReaderDialog::on_okButton_clicked()
{

}
