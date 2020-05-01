#ifndef TITLEDIALOG_H
#define TITLEDIALOG_H

#include <QDialog>

namespace Ui {
class TitleDialog;
}

class TitleDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TitleDialog(QWidget *parent = nullptr);
    ~TitleDialog();

public:
    QString getTitle();

signals:
    void titleChanged(QString);

private slots:
    void on_titleOkButton_clicked();

private:
    Ui::TitleDialog *ui;
    QString _title;
};

#endif // TITLEDIALOG_H
