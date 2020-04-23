#ifndef FILEREADERDIALOG_H
#define FILEREADERDIALOG_H

#include <QDialog>
#include <QAction>
#include <QMenuBar>
#include <QFileDialog>
#include <QFileInfo>

#include "DropWidget/droparea.h"
#include "FileReader/filereader.h"
#include "genereic/commontypes.h"

#include <vector>

namespace Ui {
class FileReaderDialog;
}

class FileReaderDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FileReaderDialog(Orientation orientation, QWidget *parent = nullptr);
    ~FileReaderDialog();

public:
    QString getFilePath();
    std::shared_ptr<FileReader> getFileReader();

private:
    void stateFileName(const QString&);

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
    Orientation file_orientation;
    std::shared_ptr<FileReader> fileReader = nullptr;
};

#endif // FILEREADERDIALOG_H
