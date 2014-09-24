#-------------------------------------------------
#
# Project created by QtCreator 2014-08-05T23:29:23
#
#-------------------------------------------------

QT       += core gui webkitwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ttyhlauncher
TEMPLATE = app

LIBS += -lquazip

SOURCES += main.cpp\
        launcherwindow.cpp \
    skinuploaddialog.cpp \
    settingsdialog.cpp \
    updatedialog.cpp \
    feedbackdialog.cpp \
    aboutdialog.cpp \
    settings.cpp \
    logger.cpp \
    util.cpp \
    reply.cpp \
    downloadmanager.cpp

HEADERS  += launcherwindow.h \
    skinuploaddialog.h \
    settingsdialog.h \
    updatedialog.h \
    feedbackdialog.h \
    aboutdialog.h \
    settings.h \
    logger.h \
    util.h \
    reply.h \
    downloadmanager.h

FORMS    += launcherwindow.ui \
    skinuploaddialog.ui \
    settingsdialog.ui \
    updatedialog.ui \
    feedbackdialog.ui \
    aboutdialog.ui

RESOURCES += \
    resources.qrc

RC_ICONS = resources/favicon.ico

ICON = resources/favicon.icns
