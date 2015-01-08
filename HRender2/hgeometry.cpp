#include "hgeometry.h"


bool HGeometry::intersectRayPlane(QVector3D rayOrigin, QVector3D rayDirection, QVector3D p0, QVector3D p1, QVector3D p2, QVector3D &resultPoint)
{
    QVector3D planeNormal = QVector3D::crossProduct(p1 - p0, p2 - p0);

    if (qFuzzyCompare(QVector3D::dotProduct(planeNormal, rayDirection), 0))
        return false;

    float s = QVector3D::dotProduct(planeNormal, p0 - rayOrigin)/QVector3D::dotProduct(planeNormal, rayDirection);

    if (s <= 0)
        return false;

    resultPoint = rayOrigin + rayDirection * s;
    return true;
}

bool HGeometry::isPointInTriangle(QVector3D p0, QVector3D p1, QVector3D p2, QVector3D point)
{
    float s1 = QVector3D::crossProduct(p0 - point, p1 - point).length();
    float s2 = QVector3D::crossProduct(p1 - point, p2 - point).length();
    float s3 = QVector3D::crossProduct(p2 - point, p0 - point).length();
    float s = QVector3D::crossProduct(p1 - p0, p2 - p0).length();

    return qFuzzyCompare(s, s1 + s2 + s3);
}
