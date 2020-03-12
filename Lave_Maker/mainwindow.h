﻿#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QFileInfo>
#include <QDebug>
#include <QMessageBox>
#include <map>
#include <QPair>
#include <tuple>

#include "filereader/filereader.h"
#include "dataTableDialog/datatabledialog.h"

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

private slots:
    void on_actionOpen_triggered();

private:
    Ui::MainWindow *ui;
    dataTableDialog* dt;
};
#endif // MAINWINDOW_H
