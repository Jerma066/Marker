#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    this->fillProjectParameters();
    connect(ui->applyButton, SIGNAL(clicked()), SLOT(accept()));

    setWindowTitle(tr("Settings of project"));
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

Settings SettingsDialog::getSettings()
{
    return current_settings;
}

void SettingsDialog::fillProjectParameters()
{
    orientationOptions.insert("Vertical", Orientation::Vertical);
    orientationOptions.insert("Horizontal", Orientation::Horizontal);
    ui->dataOrientationComboBox->addItems(QStringList(orientationOptions.keys()));

    approximationMethods.insert("Linear", ApproximationMethod::Linnear);
    ui->approximationComboBox->addItems(QStringList(approximationMethods.keys()));

    errorFunctions.insert("MSE", ErrorFunctions::MSE);
    errorFunctions.insert("MAE", ErrorFunctions::MAE);
    ui->errorComboBox->addItems(QStringList(errorFunctions.keys()));
}

void SettingsDialog::updateSettings()
{
    current_settings.data_orientation = orientationOptions[ui->dataOrientationComboBox->currentText()];
    current_settings.error_function = errorFunctions[ui->errorComboBox->currentText()];
    current_settings.approximation_method = approximationMethods[ui->approximationComboBox->currentText()];
}

void SettingsDialog::on_applyButton_clicked()
{
    this->updateSettings();
    this->hide();
}
