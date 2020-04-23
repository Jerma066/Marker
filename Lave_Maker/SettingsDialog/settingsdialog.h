#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>

#include "genereic/commontypes.h"

struct Settings{
    Orientation data_orientation;
    ApproximationMethod approximation_method;
    ErrorFunctions error_function;
};

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = nullptr);
    ~SettingsDialog();

public:
    Settings getSettings();

private slots:
    void on_applyButton_clicked();

private:
    void fillProjectParameters();
    void updateSettings();

private:
    Ui::SettingsDialog *ui;
    QMap<QString, Orientation> orientationOptions;
    QMap<QString, ApproximationMethod> approximationMethods;
    QMap<QString, ErrorFunctions> errorFunctions;
    Settings current_settings;
};

#endif // SETTINGSDIALOG_H
