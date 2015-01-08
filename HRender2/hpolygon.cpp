#include "hpolygon.h"


HPolygon::HPolygon()
{
    generateColor();
}

HPolygon::HPolygon(QVector3D a, QVector3D b, QVector3D c)
{
    av = a;
    bv = b;
    cv = c;
    generateColor();
}

bool HPolygon::detectCollision(QVector3D rayOrigin, QVector3D rayDirecction, QVector3D &collisionPoint)
{
    if (HGeometry::intersectRayPlane(rayOrigin, rayDirecction, av, bv, cv, collisionPoint))
        if (HGeometry::isPointInTriangle(av, bv, cv, collisionPoint))
            return true;

    return false;
}

void HPolygon::transform(QMatrix4x4 m)
{
    av = m * av;
    bv = m * bv;
    cv = m * cv;
}

HPolygon HPolygon::transformed(QMatrix4x4 m)
{
    HPolygon tmp = *this;
    tmp.transform(m);
    return tmp;
}

void HPolygon::generateColor()
{
    color = QColor::fromRgb(qrand() % 256, qrand() % 256, qrand() % 256);
}

QVector3D HPolygon::a() const
{
    return av;
}

void HPolygon::setA(const QVector3D &value)
{
    av = value;
}
QVector3D HPolygon::b() const
{
    return bv;
}

void HPolygon::setB(const QVector3D &value)
{
    bv = value;
}
QVector3D HPolygon::c() const
{
    return cv;
}

void HPolygon::setC(const QVector3D &value)
{
    cv = value;
}
QColor HPolygon::getColor() const
{
    return color;
}

void HPolygon::setColor(const QColor &value)
{
    color = value;
}
