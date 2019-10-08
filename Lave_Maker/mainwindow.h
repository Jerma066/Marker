#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QFileInfo>
#include <QDebug>
#include <QAxObject>
#include <QMessageBox>
#include <QMap>
#include <QtGui>
#include <QPair>
#include <tuple>

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
    void PrintData(std::tuple <QPair<QString, QString>, QMap<QString, QString>>);

private slots:
    void on_actionOpen_triggered();
    bool IsDigitalOnly(QString);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
