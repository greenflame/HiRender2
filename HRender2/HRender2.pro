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
    hcollisoninfo.cpp \
    hmaterial.cpp \
    haccuracy.cpp \
    htracer2.cpp \
    hfrustum.cpp \
    hscene.cpp \
    hray.cpp

HEADERS  += mainwindow.h \
    hpolygon.h \
    hgeometry.h \
    hcollisoninfo.h \
    hmaterial.h \
    haccuracy.h \
    htracer2.h \
    hfrustum.h \
    hscene.h \
    hray.h

FORMS    += mainwindow.ui
