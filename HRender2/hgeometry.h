#ifndef HGEOMETRY_H
#define HGEOMETRY_H

#include <QVector3D>
#include <QMatrix4x4>

#include <hray.h>

class HGeometry
{
public:
    static bool intersectLinePlane(const HRay &line, const QVector3D &p0, const QVector3D &p1, const QVector3D &p2,
                                   QVector3D &resultPoint, float &scale);
    static bool isPointInTriangle(const QVector3D &p0, const QVector3D &p1, const QVector3D &p2, const QVector3D &point);

    static bool intersectRayPolygon(const HRay &ray, const QVector3D &p0, const QVector3D &p1, const QVector3D &p2,
                                    QVector3D &resultPoint);


};

#endif // HGEOMETRY_H
