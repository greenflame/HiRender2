#ifndef HTRACER_H
#define HTRACER_H

#include <QVector>
#include <QVector3D>
#include <QMatrix4x4>
#include <QImage>

#include "hpolygon.h"
#include "hgeometry.h"

class HTracer
{
public:
    QImage traceRays(int imageHeight, int imageWidth, float left, float right, float bottom, float top, float nearPlane/*, float farPlane*/);
    QColor traceRay(QVector3D rayOrigin, QVector3D rayDirecction);

    QVector<HPolygon> polygons;

};

#endif // HTRACER_H
