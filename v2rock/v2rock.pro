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
    $$PWD/generaltab.cpp \
    $$PWD/v2rockconfig.cpp \
    $$PWD/v2rocknode.cpp \
    $$PWD/bypassiptab.cpp \
    $$PWD/bypassdomaintab.cpp \
    $$PWD/xinjieconfig.cpp \
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
    $$PWD/generaltab.h \
    $$PWD/v2rockconfig.h \
    $$PWD/v2rocknode.h \
    $$PWD/bypassiptab.h \
    $$PWD/bypassdomaintab.h \
    $$PWD/xinjieconfig.h \
    $$PWD/pingprocess.h \
    $$PWD/v2rayconfig.h \
    $$PWD/v2rayconfigroute.h \
    $$PWD/v2rayconfiglog.h \
    $$PWD/v2raydef.h \
    $$PWD/v2rayconfiginbound.h \
    $$PWD/v2rayconfigoutbound.h

FORMS += \
    $$PWD/maindialog.ui \
    $$PWD/settingsdialog.ui \
    $$PWD/generaltab.ui \
    $$PWD/bypassiptab.ui \
    $$PWD/bypassdomaintab.ui

RESOURCES += \
    $$PWD/res.qrc
