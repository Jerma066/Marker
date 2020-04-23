#include "filereaderdialog.h"
#include "ui_filereaderdialog.h"

#include <QDebug>

FileReaderDialog::FileReaderDialog(Orientation orient, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileReaderDialog),
    file_orientation(orient)
{
    ui->setupUi(this);

    // Создание области в которую можно скидывать файл с данными
    dropArea = new DropArea;
    connect(dropArea, &DropArea::changed, this, &FileReaderDialog::stateFileName);
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

// Getters
QString FileReaderDialog::getFilePath()
{
    return file_path;
}

std::shared_ptr<FileReader> FileReaderDialog::getFileReader()
{
    return fileReader;
}

void FileReaderDialog::OpenFile()
{
    file_path = QFileDialog::getOpenFileName(this, tr("Open Dialog"), "",
                                                   "XLSX (* .xlsx);;Text Files (*.txt)");
    dropArea->setText(file_path);
}

void FileReaderDialog::stateFileName(const QString& path)
{
    file_path = path;
}

void FileReaderDialog::on_okButton_clicked()
{
    QFileInfo file_info(file_path);
    fileReader = ReadFile(file_path, file_orientation);
    this->accept();
}
