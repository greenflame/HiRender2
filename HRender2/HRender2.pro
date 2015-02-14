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
    haccuracy.cpp \
    hfrustum.cpp \
    hray.cpp \
    icollider.cpp \
    hpolygoncollider.cpp \
    hspherecollider.cpp \
    hboundingspherecollider.cpp \
    htracer3.cpp \
    hcollision.cpp \
    hsphere.cpp \
    ishader.cpp \
    hphongshader.cpp \
    hskyshader.cpp \
    hmirrorshader.cpp \
    sscene.cpp \
    spolygon.cpp \
    smaterial.cpp

HEADERS  += mainwindow.h \
    haccuracy.h \
    hfrustum.h \
    hray.h \
    icollider.h \
    hpolygoncollider.h \
    hspherecollider.h \
    hboundingspherecollider.h \
    htracer3.h \
    hcollision.h \
    hsphere.h \
    ishader.h \
    hphongshader.h \
    hskyshader.h \
    hmirrorshader.h \
    sscene.h \
    spolygon.h \
    smaterial.h

FORMS    += mainwindow.ui
