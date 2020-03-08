#include "datatabledialog.h"
#include "ui_datatabledialog.h"

dataTableDialog::dataTableDialog(dataTable& data, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dataTableDialog),
    _data(data)
{
    ui->setupUi(this);
    this->createTableVidget(_data);
    this->show();
}

dataTableDialog::~dataTableDialog()
{
    delete ui;
}

void dataTableDialog::createTableVidget(const dataTable& data)
{
    ui->dataTableWidget->setColumnCount(static_cast<int>(data.size()));         // Указываем число колонок
    ui->dataTableWidget->setShowGrid(true);                                     // Включаем сетку
    ui->dataTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);  // Разрешаем выделение только одного элемента
    ui->dataTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);   // Разрешаем выделение построчно
    ui->dataTableWidget->horizontalHeader()->setStretchLastSection(true);       // Растягиваем последнюю колонку на всё доступное пространство
    //ui->dataTableWidget->verticalHeader()->hide();
    ui->dataTableWidget->horizontalHeader()->hide();

    QStringList fillCb = {"X", "Y", "X_error", "Y_error"};

    ui->dataTableWidget->insertRow(static_cast<int>(0));
    for(size_t i = 0; i < data.size(); i++){
        for(size_t j = 0; j < data[0].size(); j++ ){
            if(i == 0){
                ui->dataTableWidget->insertRow(static_cast<int>(j+1));
            }
            if(j == 0){
                QComboBox* cb = new QComboBox;
                cb->addItems(fillCb);
                cb->setProperty("col", i);
                connect(cb, SIGNAL(currentIndexChanged(int)), this, SLOT(processChangeOfCb(int)));
                ui->dataTableWidget->setCellWidget(0, static_cast<int>(i), cb);
            }
            ui->dataTableWidget->setItem(static_cast<int>(j+1), static_cast<int>(i),
                                         new QTableWidgetItem(floatToString(data[i][j])));
        }
    }
}

void dataTableDialog::processChangeOfCb(int ind_of_cbox)
{
    Q_UNUSED(ind_of_cbox)
    int index = sender()->property("col").toInt();
    qDebug() << index;
}

// Служебные функции
QString floatToString(const float& value)
{
    std::stringstream ss;
    std::string str;
    ss << value;
    ss >> str;
    return QString::fromStdString(str);
}
