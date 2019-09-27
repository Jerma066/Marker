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

void MainWindow::PrintData(QMap<QString, QString> data)
{
    for(auto& key: data.keys()){
        qDebug() << "X: " << key << "Y: " << data[key];
    }
}

void MainWindow::on_actionOpen_triggered()
{
    //Открываем диалог поиска файла и вытаскиваем путь
    QString path = QFileDialog::getOpenFileName(nullptr, tr("Open Dialog"), "", "XLSX (* .xlsx)");
    QFileInfo file_info(path);

    if(file_info.suffix() == "xlsx"){
        QAxObject* excel = new QAxObject("Excel.Application", nullptr);
        QAxObject* workbook = excel->querySubObject("Workbooks")->querySubObject("Open(const QString&)", path);
        QAxObject* sheet = workbook->querySubObject("Worksheets")->querySubObject("Item(int)", 1);

        QAxObject* columns = sheet->querySubObject("UsedRange")->querySubObject("Columns");
        int countCols = columns->property("Count").toInt();

        if(countCols == 2){
            QAxObject* rows = sheet->querySubObject("UsedRange")->querySubObject("Rows");
            int countRows = rows->property("Count").toInt();

            QString d_key;
            QString d_value;

            QMap<QString, QString> data;

            for ( int row = 0; row < countRows; row++ ){
                for ( int column = 0; column < countCols; column++ ){
                    QString value = sheet->querySubObject("Cells(int,int)", row + 1, column + 1)->property("Value").toString();

                    if(column == 0){
                        d_key = value;
                    }
                    else if(column == 1){
                        d_value = value;
                    }
                }

                data.insert(d_key, d_value);
            }

            workbook->dynamicCall("Close()");
            excel->dynamicCall("Quit()");

            PrintData(data);
        }
        else{
            QMessageBox::critical(this, tr("Error!"), tr("This is incorrect file!\n"
                                                         "Select the Excel file\n "
                                                         "you want to work with."));
        }
    }
    else if(!path.isEmpty()){
        QMessageBox::critical(this, tr("Error!"), tr("This is incorrect file!\n"
                                                     "Select the Excel file\n "
                                                     "you want to work with."));
    }
}
