#ifndef HGEOMETRY_H
#define HGEOMETRY_H

#include <QVector3D>
#include <QMatrix4x4>


class HGeometry
{
public:
    static bool intersectLinePlane(const QVector3D &l0, const QVector3D &l1,
                                   const QVector3D &p0, const QVector3D &p1, const QVector3D &p2, QVector3D &resultPoint, float &scale);
    static bool isPointInTriangle(const QVector3D &p0, const QVector3D &p1, const QVector3D &p2, const QVector3D &point);

    static bool isIntersectedIntervalPolygon(const QVector3D &intervalBegin, const QVector3D &intervalEnd,
                                  const QVector3D &p0, const QVector3D &p1, const QVector3D &p2);
    static bool intersectRayPolygon(const QVector3D &rayOrigin, const QVector3D &rayDirection,
                                  const QVector3D &p0, const QVector3D &p1, const QVector3D &p2, QVector3D &resultPoint);


};

#endif // HGEOMETRY_H
