#ifndef HGEOMETRY_H
#define HGEOMETRY_H

#include <QVector3D>
#include <QMatrix4x4>

class HGeometry
{
public:
    static bool intersectRayPlane(QVector3D rayOrigin, QVector3D rayDirection, QVector3D p0, QVector3D p1, QVector3D p2, QVector3D &resultPoint);
    static bool isPointInTriangle(QVector3D p0, QVector3D p1, QVector3D p2, QVector3D point);

};

#endif // HGEOMETRY_H
