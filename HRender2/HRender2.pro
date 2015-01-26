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
    hmaterial.cpp \
    haccuracy.cpp \
    htracer2.cpp \
    hfrustum.cpp \
    hscene.cpp \
    hray.cpp \
    icollider.cpp \
    hpolygoncollider.cpp \
    hspherecollider.cpp \
    hboundingspherecollider.cpp \
    htracer.cpp \
    htracer3.cpp \
    hcollision.cpp \
    hsphere.cpp

HEADERS  += mainwindow.h \
    hmaterial.h \
    haccuracy.h \
    htracer2.h \
    hfrustum.h \
    hscene.h \
    hray.h \
    icollider.h \
    hpolygoncollider.h \
    hspherecollider.h \
    hboundingspherecollider.h \
    htracer.h \
    htracer3.h \
    hcollision.h \
    hsphere.h

FORMS    += mainwindow.ui
