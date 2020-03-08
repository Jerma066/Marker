#ifndef DATATABLEDIALOG_H
#define DATATABLEDIALOG_H

#include <QDialog>

namespace Ui {
class dataTableDialog;
}

class dataTableDialog : public QDialog
{
    Q_OBJECT

public:
    explicit dataTableDialog(QWidget *parent = nullptr);
    ~dataTableDialog();

private:
    Ui::dataTableDialog *ui;
};

#endif // DATATABLEDIALOG_H
