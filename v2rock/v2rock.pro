#-------------------------------------------------
#
# Project created by QtCreator 2020-05-12T15:44:01
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = v2rock
TEMPLATE = app
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    $$PWD/main.cpp \
    $$PWD/maindialog.cpp \
    $$PWD/settingsdialog.cpp \
    $$PWD/settingsgeneraltab.cpp \
    $$PWD/settingsbypassdomaintab.cpp \
    $$PWD/settingsbypassiptab.cpp \
    $$PWD/v2rockconfig.cpp \
    $$PWD/v2rocknode.cpp \
    $$PWD/xinjieconfig.cpp \
    $$PWD/nodeeditdialog.cpp \
    $$PWD/nodeeditgeneraltab.cpp \
    $$PWD/nodeeditmisctab.cpp \
    $$PWD/nodeeditnetworktab.cpp \
    $$PWD/pingprocess.cpp \
    $$PWD/v2rayconfig.cpp \
    $$PWD/v2rayconfigroute.cpp \
    $$PWD/v2rayconfiglog.cpp \
    $$PWD/v2rayconfiginbound.cpp \
    $$PWD/v2rayconfigoutbound.cpp

HEADERS += \
    $$PWD/config.h \
    $$PWD/maindialog.h \
    $$PWD/settingsdialog.h \
    $$PWD/settingsgeneraltab.h \
    $$PWD/settingsbypassdomaintab.h \
    $$PWD/settingsbypassiptab.h \
    $$PWD/v2rockconfig.h \
    $$PWD/v2rocknode.h \
    $$PWD/xinjieconfig.h \
    $$PWD/nodeeditdialog.h \
    $$PWD/nodeeditgeneraltab.h \
    $$PWD/nodeeditmisctab.h \
    $$PWD/nodeeditnetworktab.h \
    $$PWD/pingprocess.h \
    $$PWD/v2rayconfig.h \
    $$PWD/v2rayconfigroute.h \
    $$PWD/v2rayconfiglog.h \
    $$PWD/v2raydef.h \
    $$PWD/v2rayconfiginbound.h \
    $$PWD/v2rayconfigoutbound.h

FORMS += \
    $$PWD/maindialog.ui \
    $$PWD/settingsbypassdomaintab.ui \
    $$PWD/settingsbypassiptab.ui \
    $$PWD/settingsdialog.ui \
    $$PWD/settingsgeneraltab.ui \
    $$PWD/nodeeditdialog.ui \
    $$PWD/nodeeditgeneraltab.ui \
    $$PWD/nodeeditmisctab.ui \
    $$PWD/nodeeditnetworktab.ui

x
RESOURCES += \
    $$PWD/res.qrc
