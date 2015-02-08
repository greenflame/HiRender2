#include "hpolygoncollider.h"


HPolygonCollider::HPolygonCollider()
{
    setUseNormals(false);
    setUseTexture(false);
}

HPolygonCollider::HPolygonCollider(QVector3D v1, QVector3D v2, QVector3D v3, IShader *shader)
{
    setV1(v1); setV2(v2); setV3(v3);

    setShader(shader);

    setUseNormals(false);
    setUseTexture(false);
}

HPolygonCollider::HPolygonCollider(const HPolygonCollider &collider)
{
    *this = collider;
}

bool HPolygonCollider::detectCollision(const HRay &ray, QVector3D &collisionPoint, ICollider **collider) const
{
    *collider = const_cast<HPolygonCollider*>(this);
    bool isCollisionPointExists = computeCollisionPoint(ray, collisionPoint);
    return isCollisionPointExists;
}

bool HPolygonCollider::processCollision(const HRay &ray, const HTracer3 &tracer, QColor &resultColor) const
{
    QVector3D collisionPoint;
    bool isCollisionPointExists = computeCollisionPoint(ray, collisionPoint);
    if (!isCollisionPointExists)
        return false;

    QVector3D collisionNormal = computeNormal(ray, collisionPoint);
    HCollision collision = HCollision(collisionPoint, collisionNormal, -ray.direction());

    resultColor = shader_->process(collision, tracer);
    return true;
}

HSphere HPolygonCollider::getBoundingSphere() const
{
    QVector3D center = (v1() + v2() + v3()) / 3;
    float r1 = center.distanceToPoint(v1());
    float r2 = center.distanceToPoint(v2());
    float r3 = center.distanceToPoint(v3());
    float radius = qMax(r1, qMax(r2, r3));
    return HSphere(center, radius);
}

ICollider *HPolygonCollider::clone() const
{
    return new HPolygonCollider(*this);
}

void HPolygonCollider::transform(const QMatrix4x4 &m)
{
    setV1(m * v1());
    setV2(m * v2());
    setV3(m * v3());

//    QMatrix4x4 im = m.inverted().;

//    im.setColumn(3, QVector4D(0, 0, 0, 1));

//    setN1(im * n1());
//    setN2(im * n2());
//    setN3(im * n3());
}

QVector3D HPolygonCollider::v1() const
{
    return v1_;
}

void HPolygonCollider::setV1(const QVector3D &value)
{
    v1_ = value;
}

QVector3D HPolygonCollider::v2() const
{
    return v2_;
}

void HPolygonCollider::setV2(const QVector3D &value)
{
    v2_ = value;
}
QVector3D HPolygonCollider::v3() const
{
    return v3_;
}

void HPolygonCollider::setV3(const QVector3D &value)
{
    v3_ = value;
}

QVector3D HPolygonCollider::n1() const
{
    return n1_;
}

void HPolygonCollider::setN1(const QVector3D &n1)
{
    n1_ = n1;
}

QVector3D HPolygonCollider::n2() const
{
    return n2_;
}

void HPolygonCollider::setN2(const QVector3D &n2)
{
    n2_ = n2;
}

QVector3D HPolygonCollider::n3() const
{
    return n3_;
}

void HPolygonCollider::setN3(const QVector3D &n3)
{
    n3_ = n3;
}

QVector3D HPolygonCollider::t1() const
{
    return t1_;
}

void HPolygonCollider::setT1(const QVector3D &t1)
{
    t1_ = t1;
}

QVector3D HPolygonCollider::t2() const
{
    return t2_;
}

void HPolygonCollider::setT2(const QVector3D &t2)
{
    t2_ = t2;
}

QVector3D HPolygonCollider::t3() const
{
    return t3_;
}

void HPolygonCollider::setT3(const QVector3D &t3)
{
    t3_ = t3;
}

IShader *HPolygonCollider::shader() const
{
    return shader_;
}

void HPolygonCollider::setShader(IShader *shader)
{
    shader_ = shader;
}

QImage *HPolygonCollider::texture() const
{
    return texture_;
}

void HPolygonCollider::setTexture(QImage *value)
{
    texture_ = value;
}
bool HPolygonCollider::useNormals() const
{
    return useNormals_;
}

void HPolygonCollider::setUseNormals(bool useNormals)
{
    useNormals_ = useNormals;
}
bool HPolygonCollider::useTexture() const
{
    return useTexture_;
}

void HPolygonCollider::setUseTexture(bool useTexture)
{
    useTexture_ = useTexture;
}

bool HPolygonCollider::computeCollisionPoint(const HRay &ray, QVector3D &collisionPoint) const
{
    QVector3D planeNormal = QVector3D::crossProduct(v2_ - v1_, v3_ - v1_).normalized();

    bool isPlaneRayParallel = HAccuracy::floatEqual(QVector3D::dotProduct(planeNormal, ray.direction()), 0);
    if (isPlaneRayParallel)
        return false;

    bool isRayOriginOnPlane = HAccuracy::floatEqual(QVector3D::dotProduct(ray.origin() - v1_, planeNormal), 0);
    if (isRayOriginOnPlane)
        return false;

    float scale = QVector3D::dotProduct(planeNormal, v1() - ray.origin()) / QVector3D::dotProduct(planeNormal, ray.direction());

    bool isPointOnRay = scale > 0;
    if (!isPointOnRay)
        return false;

    collisionPoint = ray.origin() + ray.direction() * scale;

    float angle1 = QVector3D::dotProduct((v1_ - collisionPoint).normalized(), (v2_ - collisionPoint).normalized());
    float angle2 = QVector3D::dotProduct((v2_ - collisionPoint).normalized(), (v3_ - collisionPoint).normalized());
    float angle3 = QVector3D::dotProduct((v3_ - collisionPoint).normalized(), (v1_ - collisionPoint).normalized());
    angle1 = acosf(angle1);
    angle2 = acosf(angle2);
    angle3 = acosf(angle3);
    bool isPointInTriangle = fabs((float)(M_PI * 2) - (angle1 + angle2 + angle3)) < 0.001;
    if (!isPointInTriangle)
        return false;

    return true;
}

QVector3D HPolygonCollider::computeNormal(const HRay &ray, const QVector3D &collisionPoint) const
{
    QVector3D normal;

    if (useNormals_)
    {
        // Phong interpolation
        QVector3D h1 = HLibrary::projectPointOnLine(v2_, v3_, v1_);
        QVector3D h2 = HLibrary::projectPointOnLine(v1_, v3_, v2_);
        QVector3D h3 = HLibrary::projectPointOnLine(v2_, v1_, v3_);

        QVector3D hh1 = HLibrary::projectPointOnLine(v1_, h1, collisionPoint);
        QVector3D hh2 = HLibrary::projectPointOnLine(v2_, h2, collisionPoint);
        QVector3D hh3 = HLibrary::projectPointOnLine(v3_, h3, collisionPoint);

        float k1 = 1 - (v1_ - hh1).length() / (v1_ - h1).length();
        float k2 = 1 - (v2_ - hh2).length() / (v2_ - h2).length();
        float k3 = 1 - (v3_ - hh3).length() / (v3_ - h3).length();

        normal = n1_ * k1 + n2_ * k2 + n3_ * k3;
    }
    else
    {
        normal = QVector3D::crossProduct(v2_ - v1_, v3_ - v1_);

        if (QVector3D::dotProduct(normal, ray.direction()) > 0)
            normal = -normal;

    }

    return normal.normalized();
}
