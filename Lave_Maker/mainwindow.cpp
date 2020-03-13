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

void MainWindow::PrintData(std::tuple <QPair<QString, QString>, std::map<float, float>> allData)
{
    QPair<QString, QString> labels;
    std::map<float, float> data;

    std::tie(labels, data) = allData;

    qDebug() << labels;

    for(auto it = data.begin(); it != data.end(); it++){
        qDebug() << AS_KV(it->first) <<" ; "<< AS_KV(it->second);
    }
}

void MainWindow::on_actionOpen_triggered()
{
    QString path = QFileDialog::getOpenFileName(nullptr, tr("Open Dialog"), "", "XLSX (* .xlsx);;Text Files (*.txt)");
    QFileInfo file_info(path);
    QString suffix = file_info.suffix();

    std::shared_ptr<FileReader> fr = ReadFile(path, suffix);

    std::vector<std::vector<float>> test = {{1, 2, 3},
                                            {4, 5, 6},
                                            {7, 8 ,9}};

    //Блок вызова диалогового окна
    dataTableDialog dt(test, this);
    if (dt.exec() == QDialog::Accepted)
    {
        dataTable data = dt.getDataTable();
        //TODO: дальнейшая обработка данных.
    }
}
