#include "hpolygoncollider.h"


HPolygonCollider::HPolygonCollider()
{

}

HPolygonCollider::HPolygonCollider(QVector3D a, QVector3D b, QVector3D c)
{
    setA(a);
    setB(b);
    setC(c);
}

HPolygonCollider::HPolygonCollider(QVector3D a, QVector3D b, QVector3D c, HMaterial material)
{
    setA(a);
    setB(b);
    setC(c);
    setMaterial(material);
}

HPolygonCollider::HPolygonCollider(const HPolygonCollider &collider)
{
    setA(collider.a());
    setB(collider.b());
    setC(collider.c());
    setMaterial(collider.material());
}

bool HPolygonCollider::detectCollision(const HRay &ray, HCollision &collisionInfo) const
{
    //findong collision point
    QVector3D planeNormal = QVector3D::crossProduct(b() - a(), c() - a());

    if (HAccuracy::floatEqual(QVector3D::dotProduct(planeNormal, ray.direction()), 0))  //plane and ray are parallel
        return false;

    if (HAccuracy::floatEqual(ray.origin().distanceToPlane(a(), QVector3D::crossProduct(b() - a(), c() - a()).normalized()), 0)) //ray origin on the plane
        return false;

    float scale = QVector3D::dotProduct(planeNormal, a() - ray.origin())/QVector3D::dotProduct(planeNormal, ray.direction());

    if (scale < 0) //point on the ray
        return false;

    QVector3D collisionPoint = ray.origin() + ray.direction() * scale; //result of ray plane intesetion

    float s1 = QVector3D::crossProduct(a() - collisionPoint, b() - collisionPoint).length();
    float s2 = QVector3D::crossProduct(b() - collisionPoint, c() - collisionPoint).length();
    float s3 = QVector3D::crossProduct(c() - collisionPoint, a() - collisionPoint).length();
    float s = QVector3D::crossProduct(b() - a(), c() - a()).length();

    if (!HAccuracy::floatEqual(s, s1 + s2 + s3))    //point in triangle
        return false;

    //finding collision normal
    QVector3D collisionNormal = QVector3D::crossProduct(b() - a(), c() - a());

    if (QVector3D::dotProduct(collisionNormal, ray.direction()) > 0)
        collisionNormal = -collisionNormal;

    //returning results
    collisionInfo = HCollision(collisionPoint, collisionNormal, -ray.direction(), material());
    return true;
}

HSphere HPolygonCollider::getBoundingSphere() const
{
    QVector3D center = (a() + b() + c()) / 3;
    float r1 = center.distanceToPoint(a());
    float r2 = center.distanceToPoint(b());
    float r3 = center.distanceToPoint(c());
    float radius = qMax(r1, qMax(r2, r3));
    return HSphere(center, radius);
}

ICollider *HPolygonCollider::clone() const
{
    return new HPolygonCollider(*this);
}

void HPolygonCollider::transform(const QMatrix4x4 &m)
{
    setA(m * a());
    setB(m * b());
    setC(m * c());
}

QVector3D HPolygonCollider::a() const
{
    return a_;
}

void HPolygonCollider::setA(const QVector3D &value)
{
    a_ = value;
}

QVector3D HPolygonCollider::b() const
{
    return b_;
}

void HPolygonCollider::setB(const QVector3D &value)
{
    b_ = value;
}
QVector3D HPolygonCollider::c() const
{
    return c_;
}

void HPolygonCollider::setC(const QVector3D &value)
{
    c_ = value;
}

HMaterial HPolygonCollider::material() const
{
    return material_;
}

void HPolygonCollider::setMaterial(HMaterial material)
{
    material_ = material;
}

