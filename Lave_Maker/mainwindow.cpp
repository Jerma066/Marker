#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::PrintData(std::tuple <QPair<QString, QString>, QMap<float, float>> allData)
{
    QPair<QString, QString> labels;
    QMap<float, float> data;

    std::tie(labels, data) = allData;

    qDebug() << labels;

    for(auto& key: data.keys()){
        qDebug() << AS_KV(key) <<" ; "<< AS_KV(data[key]);
    }
}

void MainWindow::on_actionOpen_triggered()
{

    QString path = QFileDialog::getOpenFileName(nullptr, tr("Open Dialog"), "", "XLSX (* .xlsx);;Text Files (*.txt)");
    QFileInfo file_info(path);
    QString suffix = file_info.suffix();

    std::shared_ptr<FileReader> fr = ReadFile(path, suffix);

    QPair<QString, QString> labels = fr->labels();
    QMap<float, float> data = fr->data();
    PrintData(std::tie(labels, data));
}
