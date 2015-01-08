#-------------------------------------------------
#
# Project created by QtCreator 2015-01-07T23:06:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HRender2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    hpolygon.cpp \
    hgeometry.cpp \
    htracer.cpp \
    hmodel.cpp

HEADERS  += mainwindow.h \
    hpolygon.h \
    hgeometry.h \
    htracer.h \
    hmodel.h

FORMS    += mainwindow.ui
