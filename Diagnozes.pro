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
    builder.cpp \
    wordranger.cpp \
    qcustomplot.cpp \
    dia.cpp \
    worddsranger.cpp \
    chainranger.cpp \
    graphicsform.cpp \
    graph.cpp \
    chaindsranger.cpp \
    histogram.cpp

HEADERS  += mainwindow.h \
    builder.h \
    wordranger.h \
    qcustomplot.h \
    dia.h \
    worddsranger.h \
    chainranger.h \
    chainranger.h \
    graphicsform.h \
    graph.h \
    source.h \
    chaindsranger.h \
    histogram.h

FORMS    += mainwindow.ui \
    dia.ui \
    graph.ui
