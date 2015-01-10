#include "hgeometry.h"


bool HGeometry::intersectLinePlane(const QVector3D &pointOnLine, const QVector3D &lineDirection, const QVector3D &p0, const QVector3D &p1, const QVector3D &p2, QVector3D &resultPoint, float &scale)
{
    QVector3D planeNormal = QVector3D::crossProduct(p1 - p0, p2 - p0);

    if (qFuzzyCompare(QVector3D::dotProduct(planeNormal, lineDirection), 0))
        return false;

    float s = QVector3D::dotProduct(planeNormal, p0 - pointOnLine)/QVector3D::dotProduct(planeNormal, lineDirection);

    scale = s;
    resultPoint = pointOnLine + lineDirection * s;
    return true;
}

bool HGeometry::isPointInTriangle(const QVector3D &p0, const QVector3D &p1, const QVector3D &p2, const QVector3D &point)
{
    float s1 = QVector3D::crossProduct(p0 - point, p1 - point).length();
    float s2 = QVector3D::crossProduct(p1 - point, p2 - point).length();
    float s3 = QVector3D::crossProduct(p2 - point, p0 - point).length();
    float s = QVector3D::crossProduct(p1 - p0, p2 - p0).length();

    return qFuzzyCompare(s, s1 + s2 + s3);
}

bool HGeometry::isIntersectedIntervalPolygon(const QVector3D &intervalBegin, const QVector3D &intervalEnd, const QVector3D &p0, const QVector3D &p1, const QVector3D &p2)
{
    QVector3D ip;
    float scale;
    if (!intersectLinePlane(intervalBegin, intervalEnd - intervalBegin, p0, p1, p2, ip, scale))
        return false;
    if (scale < 0.000001 || scale > 0.999999)
        return false;
    if (!isPointInTriangle(p0, p1, p2, ip))
        return false;

    return true;
}

bool HGeometry::intersectRayPolygon(const QVector3D &rayOrigin, const QVector3D &rayDirection, const QVector3D &p0, const QVector3D &p1, const QVector3D &p2, QVector3D &resultPoint)
{
    QVector3D ip;
    float scale;
    if (!intersectLinePlane(rayOrigin, rayDirection, p0, p1, p2, ip, scale))
        return false;
    if (scale < 0.000001)
        return false;
    if (!isPointInTriangle(p0, p1, p2, ip))
        return false;

    resultPoint = ip;
    return true;
}
