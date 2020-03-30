#ifndef FILEREADERDIALOG_H
#define FILEREADERDIALOG_H

#include <QDialog>

namespace Ui {
class FileReaderDialog;
}

class FileReaderDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FileReaderDialog(QWidget *parent = nullptr);
    ~FileReaderDialog();

private:
    Ui::FileReaderDialog *ui;
};

#endif // FILEREADERDIALOG_H
