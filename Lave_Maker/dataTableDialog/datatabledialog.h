#ifndef DATATABLEDIALOG_H
#define DATATABLEDIALOG_H

#include <QDialog>
#include <QComboBox>
#include <QVector>
#include <QDebug>
#include <QString>
#include <QStringList>
#include <vector>
#include <sstream>

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
    void processChangeOfCb(int);

private:
    void createTableVidget(const dataTable&);

private:
    Ui::dataTableDialog *ui;
    dataTable& _data;
    QVector<QComboBox*> comboBoxes;
};

//Служебные функции
QString floatToString(const float&);

#endif // DATATABLEDIALOG_H
