#-------------------------------------------------
#
# Project created by QtCreator 2017-05-23T21:49:09
#
#-------------------------------------------------

QT       += core gui
QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UploadFile
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp
#LIBS += `pkg-config opencv --libs`
#INCLUDEPATH += C:/opencv/build/include

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
