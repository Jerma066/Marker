#ifndef DATATABLEDIALOG_H
#define DATATABLEDIALOG_H

#include <QDialog>
#include <QComboBox>
#include <QSpinBox>
#include <QVector>
#include <QDebug>
#include <QString>
#include <QStringList>
#include <QHBoxLayout>

#include <vector>
#include <sstream>
#include <set>
#include <map>
#include <array>

#include "vecOperators/vecoperators.h"
#include "genereic/commontypes.h"

class TableDinamicWidgets{
public:
    TableDinamicWidgets();
    TableDinamicWidgets(QWidget*, QHBoxLayout*, QComboBox*, QSpinBox*);
    ~TableDinamicWidgets() = default;

    QWidget* general_wid;
    QHBoxLayout* wid_layout;
    QComboBox* wid_comboBox;
    QSpinBox* wid_spinBox;
};

namespace Ui {
class dataTableDialog;
}

class dataTableDialog : public QDialog
{
    Q_OBJECT

public:
    explicit dataTableDialog(dataTable& data, QWidget *parent = nullptr);
    ~dataTableDialog();

public:
   dataTable getDataTable();
   allGraphsData getAllGraphsData();

private slots:
    void on_okButton_clicked();
    void TableElementChanged(int, int);

private:
    void createTableVidget(const dataTable&);
    graphhDataFrame createDataFrameObj(const int& index);

private:
    Ui::dataTableDialog *ui;
    dataTable _data;
    std::vector<QString> _labels;
    const dataTable file_data;
    QVector<TableDinamicWidgets> topTableWidgets;
    std::vector<graphhDataFrame> allGraphsFrame;
};

//Служебные функции
QString floatToString(const float&);

#endif // DATATABLEDIALOG_H
