#-------------------------------------------------
#
# Project created by QtCreator 2014-08-05T23:29:23
#
#-------------------------------------------------

QT       += core gui webkitwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ttyhlauncher
TEMPLATE = app


SOURCES += main.cpp\
        launcherwindow.cpp \
    passworddialog.cpp \
    skinuploaddialog.cpp \
    settingsdialog.cpp \
    updatedialog.cpp \
    feedbackdialog.cpp \
    aboutdialog.cpp \
    settings.cpp

HEADERS  += launcherwindow.h \
    passworddialog.h \
    skinuploaddialog.h \
    settingsdialog.h \
    updatedialog.h \
    feedbackdialog.h \
    aboutdialog.h \
    settings.h

FORMS    += launcherwindow.ui \
    passworddialog.ui \
    skinuploaddialog.ui \
    settingsdialog.ui \
    updatedialog.ui \
    feedbackdialog.ui \
    aboutdialog.ui

RESOURCES += \
    resources.qrc
