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
    htracer3.cpp \
    sscene.cpp \
    spolygon.cpp \
    smaterial.cpp \
    hfrustum.cpp \
    hray.cpp \
    hsphere.cpp \
    colliders/icollider.cpp \
    colliders/hboundingspherecollider.cpp \
    colliders/hpolygoncollider.cpp \
    colliders/hspherecollider.cpp \
    shaders/hmirrorshader.cpp \
    shaders/hphongshader.cpp \
    shaders/hskyshader.cpp \
    shaders/ishader.cpp \
    hcollision.cpp \
    math/haccuracy.cpp

HEADERS  += mainwindow.h \
    htracer3.h \
    sscene.h \
    spolygon.h \
    smaterial.h \
    hfrustum.h \
    hray.h \
    hsphere.h \
    colliders/icollider.h \
    colliders/hboundingspherecollider.h \
    colliders/hpolygoncollider.h \
    colliders/hspherecollider.h \
    shaders/ishader.h \
    shaders/hmirrorshader.h \
    shaders/hphongshader.h \
    shaders/hskyshader.h \
    hcollision.h \
    math/haccuracy.h \
    shaders/hshaders.h \
    colliders/hcolliders.h

FORMS    += mainwindow.ui
