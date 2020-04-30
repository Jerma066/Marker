#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QFileInfo>
#include <QDebug>
#include <QMessageBox>
#include <QPair>
#include <QPixmap>

#include <map>
#include <tuple>

#include "CustomViewElements/Switch/switch.h"
#include "FileReaderDialog/filereaderdialog.h"
#include "dataTableDialog/datatabledialog.h"
#include "SettingsDialog/settingsdialog.h"
#include "GraphWindow/graphwindow.h"

#define AS_KV(x)  #x << " = " << x

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void PrintData(std::tuple <QPair<QString, QString>, std::map<float, float>>);
    void setStyle(int);

private slots:
    void on_newProjectButton_clicked();
    void FileReadingStage(const Settings&);
    void DataProcessingStage(std::vector<std::vector<float>>&);

private:
    Ui::MainWindow *ui;
    Switch* style_switch;
    GraphWindow* gr_win;

};
#endif // MAINWINDOW_H
