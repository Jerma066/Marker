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

#include "vecOperators/vecoperators.h"

class TableDinamicWidgets{
public:
    TableDinamicWidgets();
    TableDinamicWidgets(QWidget*, QHBoxLayout*, QComboBox*, QSpinBox*);
    ~TableDinamicWidgets();

    QWidget* general_wid;
    QHBoxLayout* wid_layout;
    QComboBox* wid_comboBox;
    QSpinBox* wid_spinBox;
};

namespace Ui {
class dataTableDialog;
}

typedef std::vector<std::vector<float>> dataTable;

class dataTableDialog : public QDialog
{
    Q_OBJECT

public:
    explicit dataTableDialog(dataTable& data, QWidget *parent = nullptr);
    ~dataTableDialog();

private slots:
    void on_okButton_clicked();
    void TableElementChanged(int, int);

private:
    void createTableVidget(const dataTable&);

private:
    Ui::dataTableDialog *ui;
    dataTable _data;
    std::vector<QString> _labels;
    const dataTable file_data;
    QVector<TableDinamicWidgets> topTableWidgets;
};

//Служебные функции
QString floatToString(const float&);

#endif // DATATABLEDIALOG_H
