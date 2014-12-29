#-------------------------------------------------
#
# Project created by QtCreator 2014-10-25T13:48:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = trackingGUI_opencv
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

LIBS += `pkg-config opencv --libs`

FORMS    += mainwindow.ui
