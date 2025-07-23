#-------------------------------------------------
#
# Project created by QtCreator 2025-06-23T14:49:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = recdir
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Core/profilegenerator.cpp

HEADERS  += mainwindow.h \
    Core/profilegenerator.h

FORMS    += mainwindow.ui
