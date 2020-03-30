#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap markerLogo(":/images/img/MarkerLogo.png");
    ui->markerLogoImg->setPixmap(markerLogo.scaled(ui->markerLogoImg->width(),
                                                   ui->markerLogoImg->height()));

    //Switch of style
    style_switch = new Switch("Style:");
    style_switch->setLayoutDirection(Qt::RightToLeft);
    ui->styleSwitchLayout->addWidget(style_switch);
    connect(style_switch, SIGNAL(stateChanged(int)), this, SLOT(setStyle(int)));

    setWindowTitle(tr("Marker"));
}

MainWindow::~MainWindow()
{
    delete style_switch;
    delete ui;
}

void MainWindow::PrintData(std::tuple <QPair<QString, QString>, std::map<float, float>> allData)
{
    QPair<QString, QString> labels;
    std::map<float, float> data;

    std::tie(labels, data) = allData;

    qDebug() << labels;

    for(auto it = data.begin(); it != data.end(); it++){
        qDebug() << AS_KV(it->first) <<" ; "<< AS_KV(it->second);
    }
}

void MainWindow::on_newProjectButton_clicked()
{
    auto fr = new FileReaderDialog(this);
    Q_UNUSED(fr)
}

/*
void MainWindow::on_actionOpen_triggered()
{

    QString path = QFileDialog::getOpenFileName(nullptr, tr("Open Dialog"), "", "XLSX (* .xlsx);;Text Files (*.txt)");
    QFileInfo file_info(path);
    QString suffix = file_info.suffix();

    std::shared_ptr<FileReader> fr = ReadFile(path, suffix, Orientation::Vertical);

    std::vector<std::vector<float>> test = fr->data();

    //Блок вызова диалогового окна
    dataTableDialog dt(test, this);
    if (dt.exec() == QDialog::Accepted)
    {
        dataTable data = dt.getDataTable();
        //TODO: дальнейшая обработка данных.
    }
}
*/

//Style settings
void MainWindow::setStyle(int state)
{
    if(state ==  Qt::Checked){
        // Создаём палитру для тёмной темы оформления
        QPalette darkPalette;

        // Настраиваем палитру для цветовых ролей элементов интерфейса
        darkPalette.setColor(QPalette::Window, QColor(53, 53, 53));
        darkPalette.setColor(QPalette::WindowText, Qt::white);
        darkPalette.setColor(QPalette::Base, QColor(25, 25, 25));
        darkPalette.setColor(QPalette::AlternateBase, QColor(53, 53, 53));
        darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
        darkPalette.setColor(QPalette::ToolTipText, Qt::white);
        darkPalette.setColor(QPalette::Text, Qt::white);
        darkPalette.setColor(QPalette::Button, QColor(53, 53, 53));
        darkPalette.setColor(QPalette::ButtonText, Qt::white);
        darkPalette.setColor(QPalette::BrightText, Qt::red);
        darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
        darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
        darkPalette.setColor(QPalette::HighlightedText, Qt::black);

        // Устанавливаем данную палитру
        qApp->setPalette(darkPalette);
    }
    else if(state == Qt::Unchecked){
        // Установить стандартной палитры из темы оформления
        qApp->setPalette(style()->standardPalette());
    }
}
