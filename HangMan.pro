#-------------------------------------------------
#
# Project created by QtCreator 2016-05-02T17:15:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HangMan
TEMPLATE = app


SOURCES += main.cpp\
        Controller/mainview.cpp \
    Model/hangmangame.cpp

HEADERS  += Controller/mainview.h \
    Model/hangmangame.h

FORMS    += View/mainview.ui

RESOURCES += \
    stuff.qrc
