#-------------------------------------------------
#
# Project created by QtCreator 2015-09-08T00:24:45
#
#-------------------------------------------------

CONFIG += c++11
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = x_and_0
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    myfield.cpp \
    ai.cpp

HEADERS  += mainwindow.h \
    myfield.h \
    ai.h \
    enum_class_stage.h \
    enum_iscross.h \
    figure_enum_class.h \
    figure_enum.h

FORMS    += mainwindow.ui
