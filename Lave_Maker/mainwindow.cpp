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

void MainWindow::PrintData(std::tuple <QPair<QString, QString>, QMap<QString, QString>> allData)
{
    QPair<QString, QString> labels;
    QMap<QString, QString> data;

    std::tie(labels, data) = allData;

    qDebug() << labels;

    for(auto& key: data.keys()){
        qDebug() << "X: " << key << "Y: " << data[key];
    }
}

bool MainWindow::IsDigitalOnly(QString str)
{
    foreach(QChar c, str)
    {
        if(c < '0' || c > '9')
            return false;
    }

    return true;
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

            QString d_key = "";
            QString d_value = "";

            QMap<QString, QString> data;

            d_key   = sheet->querySubObject("Cells(int,int)", 1, 1)->property("Value").toString();
            d_value = sheet->querySubObject("Cells(int,int)", 1, 2)->property("Value").toString();

            QPair<QString, QString> labels;
            if(!IsDigitalOnly(d_key) || !IsDigitalOnly(d_value)){
                labels = {d_key, d_value};

            }
            else {
                data.insert(d_key, d_value);
            }

            for ( int row = 1; row < countRows; row++ ){
                for ( int column = 1; column < countCols; column++ ){

                    if(column == 0){
                        d_key = sheet->querySubObject("Cells(int,int)", row + 1, column + 1)->property("Value").toString();
                    }
                    else if(column == 1){
                        d_value = sheet->querySubObject("Cells(int,int)", row + 1, column + 1)->property("Value").toString();
                    }
                }

                data.insert(d_key, d_value);
            }

            PrintData(std::tie(labels, data));

            workbook->dynamicCall("Close()");
            excel->dynamicCall("Quit()");

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
