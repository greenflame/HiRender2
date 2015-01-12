#include "hgeometry.h"


bool HGeometry::intersectLinePlane(const HRay &line, const QVector3D &p0, const QVector3D &p1, const QVector3D &p2, QVector3D &resultPoint, float &scale)
{
    QVector3D planeNormal = QVector3D::crossProduct(p1 - p0, p2 - p0);

    if (qFuzzyCompare(QVector3D::dotProduct(planeNormal, line.direction()), 0))
        return false;

    float s = QVector3D::dotProduct(planeNormal, p0 - line.origin())/QVector3D::dotProduct(planeNormal, line.direction());

    scale = s;
    resultPoint = line.origin() + line.direction() * s;
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

bool HGeometry::intersectRayPolygon(const HRay &ray, const QVector3D &p0, const QVector3D &p1, const QVector3D &p2, QVector3D &resultPoint)
{
    QVector3D ip;
    float scale;
    if (!intersectLinePlane(ray, p0, p1, p2, ip, scale))
        return false;
    if (scale < 0.0001)
        return false;
    if (!isPointInTriangle(p0, p1, p2, ip))
        return false;

    resultPoint = ip;
    return true;
}
