QT       += core gui axcontainer
# Для использования QAxObject добавим axcontainer

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    CustomViewElements/Switch/switch.cpp \
    FileReaderDialog/DropWidget/droparea.cpp \
    FileReaderDialog/FileReader/filereader.cpp \
    FileReaderDialog/filereaderdialog.cpp \
    GraphWindow/GraphObject/dependances/coefficients_functions.cpp \
    GraphWindow/GraphObject/dependances/dependances.cpp \
    GraphWindow/GraphObject/dependances/errors.cpp \
    GraphWindow/GraphObject/graphobject.cpp \
    GraphWindow/graphwindow.cpp \
    GraphWindow/qcustomplot.cpp \
    SettingsDialog/settingsdialog.cpp \
    dataTableDialog/datatabledialog.cpp \
    dataTableDialog/vecOperators/vecoperators.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    CustomViewElements/Switch/switch.h \
    CustomViewElements/Switch/switch_style.h \
    FileReaderDialog/DropWidget/droparea.h \
    FileReaderDialog/FileReader/filereader.h \
    FileReaderDialog/filereaderdialog.h \
    GraphWindow/GraphObject/dependances/coefficients_functions.h \
    GraphWindow/GraphObject/dependances/dependances.h \
    GraphWindow/GraphObject/dependances/errors.h \
    GraphWindow/GraphObject/graphobject.h \
    GraphWindow/graphwindow.h \
    GraphWindow/qcustomplot.h \
    SettingsDialog/settingsdialog.h \
    dataTableDialog/datatabledialog.h \
    dataTableDialog/vecOperators/vecoperators.h \
    genereic/commontypes.h \
    mainwindow.h

FORMS += \
    FileReaderDialog/filereaderdialog.ui \
    GraphWindow/graphwindow.ui \
    SettingsDialog/settingsdialog.ui \
    dataTableDialog/datatabledialog.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
