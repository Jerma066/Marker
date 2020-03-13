#include "datatabledialog.h"
#include "ui_datatabledialog.h"

dataTableDialog::dataTableDialog(dataTable& data, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dataTableDialog),
    _data(data),
    file_data(data)
{
    ui->setupUi(this);
    this->createTableVidget(_data);
    connect(ui->okButton, SIGNAL(clicked()), SLOT(accept()));
}

dataTableDialog::~dataTableDialog()
{
    for(auto wid = topTableWidgets.begin(); wid < topTableWidgets.end(); wid++){
        delete wid->wid_spinBox;
        delete wid->wid_comboBox;
        delete wid->wid_layout;
        delete wid->general_wid;
    }

    topTableWidgets.clear();
    delete ui;
}

dataTable dataTableDialog::getDataTable()
{
    return _data;
}

void dataTableDialog::createTableVidget(const dataTable& data)
{
    ui->dataTableWidget->setColumnCount(static_cast<int>(data.size()));         // Указываем число колонок
    ui->dataTableWidget->setShowGrid(true);                                     // Включаем сетку
    ui->dataTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);  // Разрешаем выделение только одного элемента
    ui->dataTableWidget->verticalHeader()->hide();

    QStringList fillCb = {"X", "Y", "X_error", "Y_error"};

    ui->dataTableWidget->insertRow(static_cast<int>(0));
    for(size_t i = 0; i < data.size(); i++){
        for(size_t j = 0; j < data[0].size(); j++ ){
            if(i == 0){
                ui->dataTableWidget->insertRow(static_cast<int>(j+1));
            }
            if(j == 0){
                QHBoxLayout *l = new QHBoxLayout();
                l->setMargin(1);
                l->setSpacing(0);
                QComboBox* cb = new QComboBox;
                cb->addItems(fillCb);
                l->addWidget(cb);
                QSpinBox* sb = new QSpinBox;
                l->addWidget(sb);
                QWidget *w = new QWidget();
                w->setLayout(l);
                TableDinamicWidgets item = TableDinamicWidgets(w, l, cb, sb);
                topTableWidgets.push_back(item);

                ui->dataTableWidget->setColumnWidth(static_cast<int>(i), 150);
                ui->dataTableWidget->setCellWidget(0, static_cast<int>(i), w);
            }
            ui->dataTableWidget->setItem(static_cast<int>(j+1), static_cast<int>(i),
                                         new QTableWidgetItem(floatToString(data[i][j])));
        }
    }

    ui->dataTableWidget->horizontalHeader()->setStretchLastSection(true);
    connect(ui->dataTableWidget, SIGNAL(cellChanged(int, int)),
            this, SLOT(TableElementChanged(int, int)));
}

void dataTableDialog::TableElementChanged(int row, int column)
{
    _data[static_cast<size_t>(column)][static_cast<size_t>(row - 1)] =
            ui->dataTableWidget->item(row, column)->text().toFloat();

    qDebug() << _data[1][2];
    qDebug() << file_data[1][2];
}

void dataTableDialog::on_okButton_clicked()
{
    // TODO: Проверка корректности заполненых full_label-ов
    // TODO: Дальнешая обработка данных
    for(auto wid_elem = topTableWidgets.begin();
        wid_elem < topTableWidgets.end(); wid_elem++)
    {
        QString full_label = wid_elem->wid_comboBox->currentText() + QString::number(wid_elem->wid_spinBox->value());
    }

    // Проверка изменений данных
    // TODO: высплывающее диалоговое окно оповещающее об
    //       изменении данных
    if(_data != file_data){
        qDebug() << "The read data has been changed."\
                    "\nWant to overwrite a read file?";
    }
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

// Класс для хранения динамически выделенных виджетов
TableDinamicWidgets::TableDinamicWidgets():
    general_wid(nullptr),
    wid_layout(nullptr),
    wid_comboBox(nullptr),
    wid_spinBox(nullptr)
{
}

TableDinamicWidgets::TableDinamicWidgets(QWidget* g_w, QHBoxLayout* w_l, QComboBox* w_cb, QSpinBox* w_sb):
    general_wid(g_w),
    wid_layout(w_l),
    wid_comboBox(w_cb),
    wid_spinBox(w_sb)
{
}
