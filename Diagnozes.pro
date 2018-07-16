#-------------------------------------------------
#
# Project created by QtCreator 2018-07-11T00:29:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = Diagnozes
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    warehouse.cpp \
    worker.cpp \
    builder.cpp \
    wordranger.cpp \
    qcustomplot.cpp \
    dia.cpp \
    worddsranger.cpp

HEADERS  += mainwindow.h \
    warehouse.h \
    worker.h \
    builder.h \
    wordranger.h \
    qcustomplot.h \
    dia.h \
    worddsranger.h \
    chainranger.h

FORMS    += mainwindow.ui \
    dia.ui
