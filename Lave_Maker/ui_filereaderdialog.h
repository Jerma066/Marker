/********************************************************************************
** Form generated from reading UI file 'filereaderdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILEREADERDIALOG_H
#define UI_FILEREADERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_FileReaderDialog
{
public:
    QGridLayout *gridLayout_2;
    QPushButton *okButton;
    QSpacerItem *horizontalSpacer;
    QGridLayout *drLayout;

    void setupUi(QDialog *FileReaderDialog)
    {
        if (FileReaderDialog->objectName().isEmpty())
            FileReaderDialog->setObjectName(QString::fromUtf8("FileReaderDialog"));
        FileReaderDialog->resize(418, 343);
        gridLayout_2 = new QGridLayout(FileReaderDialog);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        okButton = new QPushButton(FileReaderDialog);
        okButton->setObjectName(QString::fromUtf8("okButton"));

        gridLayout_2->addWidget(okButton, 1, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 1, 0, 1, 1);

        drLayout = new QGridLayout();
        drLayout->setObjectName(QString::fromUtf8("drLayout"));

        gridLayout_2->addLayout(drLayout, 0, 0, 1, 2);


        retranslateUi(FileReaderDialog);

        QMetaObject::connectSlotsByName(FileReaderDialog);
    } // setupUi

    void retranslateUi(QDialog *FileReaderDialog)
    {
        FileReaderDialog->setWindowTitle(QApplication::translate("FileReaderDialog", "Dialog", nullptr));
        okButton->setText(QApplication::translate("FileReaderDialog", "Ok", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FileReaderDialog: public Ui_FileReaderDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILEREADERDIALOG_H
