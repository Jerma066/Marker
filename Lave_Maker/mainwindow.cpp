#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)
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
    delete gr_win;
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
    //Блок вызова диалогового окна
    SettingsDialog sd(this);
    if (sd.exec() == QDialog::Accepted)
    {
        cur_state_of_project = sd.getSettings();
        FileReadingStage(cur_state_of_project);
    }
}

void MainWindow::FileReadingStage(const Settings& state_of_project)
{
    FileReaderDialog frd(state_of_project.data_orientation, this);
    if (frd.exec() == QDialog::Accepted)
    {
        // TODO: Нужно попыпаться использовать move-семантику, если это допустимо
        std::shared_ptr<FileReader> fr = frd.getFileReader();
        std::vector<std::vector<float>> data = fr->data();
        DataProcessingStage(data);
    }
}

void MainWindow::DataProcessingStage(std::vector<std::vector<float>>& data)
{
    dataTableDialog dt(data, this);
    if (dt.exec() == QDialog::Accepted)
    {
        allGraphsData gdata = dt.getAllGraphsData();
        gr_win = new GraphWindow(gdata, cur_state_of_project.approximation_method,
                                 cur_state_of_project.error_function, this);
    }
}

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
