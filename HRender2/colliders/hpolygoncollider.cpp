#include "hpolygoncollider.h"


HPolygonCollider::HPolygonCollider()
{
    setUseNormals(false);
    setUseTexture(false);
}

HPolygonCollider::HPolygonCollider(QVector3D v1, QVector3D v2, QVector3D v3, IShader *shader)
{
    setV1(v1);
    setV2(v2);
    setV3(v3);

    setShader(shader);

    setUseNormals(false);
    setUseTexture(false);
}

HPolygonCollider::HPolygonCollider(const HPolygonCollider &collider)
{
    *this = collider;
}

// http://www.ray-tracing.ru/articles213.html
// http://en.wikipedia.org/wiki/Möller–Trumbore_intersection_algorithm
bool HPolygonCollider::detectCollision(const HRay &ray, QVector3D &collisionPoint, ICollider **collider) const
{
    *collider = const_cast<HPolygonCollider*>(this);

    float EPSILON = 0.0001; //xm..

    // Ray origin too close to plane
    if (ray.origin().distanceToPlane(v1_, v2_, v3_) < EPSILON)
    {
        return false;
    }

    // Find vectors for two edges sharing V1
    QVector3D e1 = v2_ - v1_;
    QVector3D e2 = v3_ - v1_;

    // Begin calculating determinant - also used to calculate u parameter
    QVector3D P = QVector3D::crossProduct(ray.direction(), e2);

    // If determinant is near zero, ray lies in plane of triangle
    float det = QVector3D::dotProduct(e1, P);

    // NOT CULLING
    if(det > -EPSILON && det < EPSILON)
    {
        return false;
    }

    float inv_det = 1.f / det;

    // Calculate distance from V1 to ray origin
    QVector3D T =  ray.origin() - v1_;

    // Calculate u parameter and test bound
    float u = QVector3D::dotProduct(T, P) * inv_det;

    // The intersection lies outside of the triangle
    if(u < 0.f || u > 1.f)
    {
        return false;
    }

    // Prepare to test v parameter
    QVector3D Q = QVector3D::crossProduct(T, e1);

    // Calculate V parameter and test bound
    float v = QVector3D::dotProduct(ray.direction(), Q) * inv_det;

    // The intersection lies outside of the triangle
    if(v < 0.f || u + v  > 1.f)
    {
        return false;
    }

    float t = QVector3D::dotProduct(e2, Q) * inv_det;

    // Ray intersection
    if(t > EPSILON)
    {
        collisionPoint = ray.origin() + ray.direction() * t;
        return true;
    }

    // No hit, no win
    return false;
}

bool HPolygonCollider::processCollision(const HRay &ray, const HTracer3 &tracer, QColor &resultColor, QStack<IShader *> &shaderStack) const
{
    // Computing collision point
    QVector3D collisionPoint;
    bool isCollisionPointExists = ICollider::detectCollision(ray, collisionPoint);
    if (!isCollisionPointExists)
        return false;

    // Computing collision notmal
    QVector3D collisionNormal;

    if (useNormals_)    // Interpolate existing normals
    {
        // Phong interpolation
        float s = QVector3D::crossProduct(v3_ - v1_, v2_ - v1_).length();

        float k1 = QVector3D::crossProduct(v3_ - v2_, collisionPoint - v2_).length() / s;
        float k2 = QVector3D::crossProduct(v3_ - v1_, collisionPoint - v1_).length() / s;
        float k3 = QVector3D::crossProduct(v1_ - v2_, collisionPoint - v2_).length() / s;

        collisionNormal = n1_ * k1 + n2_ * k2 + n3_ * k3;
    }
    else    // Compute auto normal [taking into account ray direction]
    {
        collisionNormal = QVector3D::crossProduct(v2_ - v1_, v3_ - v1_);

        if (QVector3D::dotProduct(collisionNormal, ray.direction()) > 0)
            collisionNormal = -collisionNormal;

    }

    collisionNormal.normalize();    // Defenition of normal..


    HCollision collision = HCollision(collisionPoint, collisionNormal, -ray.direction());
    resultColor = shader_->process(collision, tracer, shaderStack);
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

    // Apply only rotation to normals
    setN1(QVector3D(m * QVector4D(n1_, 0)));
    setN2(QVector3D(m * QVector4D(n2_, 0)));
    setN3(QVector3D(m * QVector4D(n3_, 0)));
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
