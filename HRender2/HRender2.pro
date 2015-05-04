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
    colliders/icollider.cpp \
    colliders/hboundingspherecollider.cpp \
    colliders/hpolygoncollider.cpp \
    shaders/hmirrorshader.cpp \
    shaders/hphongshader.cpp \
    shaders/hskyshader.cpp \
    htilecontroller.cpp \
    shaders/hambientocclusionshader.cpp \
    shaders/hrefractionshader.cpp \
    geometry/hray.cpp \
    geometry/hcollision.cpp \
    geometry/hfrustum.cpp \
    geometry/hsphere.cpp \
    shaders/ishader.cpp \
    hbvh.cpp \
    shaders/hmixshader.cpp

HEADERS  += mainwindow.h \
    htracer3.h \
    sscene.h \
    spolygon.h \
    smaterial.h \
    colliders/icollider.h \
    colliders/hboundingspherecollider.h \
    colliders/hpolygoncollider.h \
    shaders/ishader.h \
    shaders/hmirrorshader.h \
    shaders/hphongshader.h \
    shaders/hskyshader.h \
    shaders/hshaders.h \
    colliders/hcolliders.h \
    htilecontroller.h \
    shaders/hambientocclusionshader.h \
    shaders/hrefractionshader.h \
    geometry/hray.h \
    geometry/hcollision.h \
    geometry/hfrustum.h \
    geometry/hsphere.h \
    hbvh.h \
    shaders/hmixshader.h

FORMS    += mainwindow.ui
