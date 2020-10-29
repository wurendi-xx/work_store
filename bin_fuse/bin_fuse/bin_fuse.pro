#-------------------------------------------------
#
# Project created by QtCreator 2020-07-09T16:44:25
#
#-------------------------------------------------

QT       += core gui
QT      += serialport
QT       += axcontainer
QT       +=sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = bin_fuse
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    form_bin_fuse.cpp \
    wizard_bin_fuse.cpp \
    wizard_bin_menu.cpp \
    form_bin_menu.cpp \
    bluetooth.cpp

HEADERS += \
        mainwindow.h \
    form_bin_fuse.h \
    wizard_bin_fuse.h \
    wizard_bin_menu.h \
    parameter.h \
    form_bin_menu.h \
    bluetooth.h

FORMS += \
        mainwindow.ui \
    form_bin_fuse.ui \
    bluetooth.ui

STATECHARTS += \
    ../../journey of qt/lesson-5/StandardDialogs/test.scxml

RESOURCES += \
    tineco_logo.qrc
