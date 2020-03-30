#ifndef FILEREADERDIALOG_H
#define FILEREADERDIALOG_H

#include <QDialog>
#include <QAction>
#include <QMenuBar>
#include <QFileDialog>
#include <QFileInfo>

#include "DropWidget/droparea.h"

#include <vector>

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
    void getFileName(const QString&);

private slots:
    void OpenFile();

    void on_okButton_clicked();

private:
    Ui::FileReaderDialog *ui;
    DropArea *dropArea;
    std::vector<QAction*> menuBarActions;
    QMenuBar* menuBar;
    QMenu*  fileMenu;
    QString file_path;
};

#endif // FILEREADERDIALOG_H
