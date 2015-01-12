#include "hpolygon.h"


HPolygon::HPolygon()
{
    generateColor();
}

HPolygon::HPolygon(QVector3D a, QVector3D b, QVector3D c)
{
    a_ = a;
    b_ = b;
    c_ = c;
    generateColor();
}

bool HPolygon::detectCollision(const HRay &ray, HCollisonInfo &collisionInfo) const
{
    QVector3D collisionPoint, collisionNormal;

    if (!HGeometry::intersectRayPolygon(ray, a_, b_, c_, collisionPoint))
        return false;

    collisionNormal = QVector3D::crossProduct(b_ - a_, c_ - a_);

    if (QVector3D::dotProduct(collisionNormal, ray.direction()) > 0)
        collisionNormal = -collisionNormal;

    collisionInfo = HCollisonInfo(collisionPoint, collisionNormal, -ray.direction(), material_);
    return true;
}

void HPolygon::transform(const QMatrix4x4 &m)
{
    a_ = m * a_;
    b_ = m * b_;
    c_ = m * c_;
}

HPolygon HPolygon::transformed(const QMatrix4x4 &m) const
{
    HPolygon tmp = *this;
    tmp.transform(m);
    return tmp;
}

void HPolygon::generateColor()
{
//    material_ = QColor::fromRgb(qrand() % 256, qrand() % 256, qrand() % 256);
    material_.setDiffuseColor(Qt::gray);
}

QVector3D HPolygon::a() const
{
    return a_;
}

void HPolygon::setA(const QVector3D &value)
{
    a_ = value;
}

QVector3D HPolygon::b() const
{
    return b_;
}

void HPolygon::setB(const QVector3D &value)
{
    b_ = value;
}
QVector3D HPolygon::c() const
{
    return c_;
}

void HPolygon::setC(const QVector3D &value)
{
    c_ = value;
}

HMaterial HPolygon::material() const
{
    return material_;
}

void HPolygon::setMaterial(const HMaterial &material)
{
    material_ = material;
}

