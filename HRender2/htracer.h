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
    QColor traceRay(const QVector3D &rayOrigin, const QVector3D &rayDirecction);

    bool findClosestCollision(const QVector3D &rayOrigin, const QVector3D &rayDirecction, HCollisonInfo &collisionInfo) const;

    float lambertLightness(const HCollisonInfo &ci) const;
    bool isPointInShadow(const QVector3D point) const;

    static QColor mixColors(const QColor &c1, const QColor &c2, float k1, float k2);

    QVector<HPolygon> polygons;
    QVector3D lamp;
};

#endif // HTRACER_H
