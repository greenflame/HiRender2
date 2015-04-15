#include "hspherecollider.h"

HSphereCollider::HSphereCollider()
{

}

HSphereCollider::HSphereCollider(HSphere sphere)
{
    setSphere(sphere);
}

HSphereCollider::HSphereCollider(HSphere sphere, IShader *shader)
{
    setSphere(sphere);
    setShader(shader);
}

HSphereCollider::HSphereCollider(const HSphereCollider &collider)
{
    *this = collider;
}

bool HSphereCollider::detectCollision(const HRay &ray, QVector3D &collisionPoint, ICollider **collider) const
{
    HCollision collision;
    bool isCollisionExists = localDetectCollision(ray, collision);

    if (isCollisionExists)
    {
        *collider = const_cast<HSphereCollider*>(this);
        collisionPoint = collision.point();
        return true;
    }

    return false;
}

bool HSphereCollider::processCollision(const HRay &ray, const HTracer3 &tracer, QColor &resultColor) const
{
    HCollision collision;
    bool isCollisionExists = localDetectCollision(ray, collision);

    if (isCollisionExists)
    {
        resultColor = shader_->process(collision, tracer);
        return true;
    }

    return false;
}

HSphere HSphereCollider::getBoundingSphere() const
{
    return sphere_;
}

ICollider *HSphereCollider::clone() const
{
    return new HSphereCollider(*this);
}

void HSphereCollider::transform(const QMatrix4x4 &m)
{
    sphere_.setCenter(m * sphere_.center());
}

HSphere HSphereCollider::sphere() const
{
    return sphere_;
}

void HSphereCollider::setSphere(const HSphere &sphere)
{
    sphere_ = sphere;
}

IShader *HSphereCollider::shader() const
{
    return shader_;
}

void HSphereCollider::setShader(IShader *shader)
{
    shader_ = shader;
}

bool HSphereCollider::localDetectCollision(const HRay &ray, HCollision &collisionInfo) const
{
    if (sphere_.center().distanceToLine(ray.origin(), ray.direction()) > sphere_.radius())    //no intersections
        return false;

    if (HAccuracy::floatEqual(sphere_.center().distanceToPoint(ray.origin()), sphere_.radius()) /*&&
            QVector3D::dotProduct(ray.origin() - sphere_.center(), ray.direction()) > 0*/)    //ray origin on the sphere and directed outside
        return false;

    QVector3D v = sphere_.center() - ray.origin();
    QVector3D proj = ray.origin() + QVector3D::dotProduct(v, ray.direction())
            / QVector3D::dotProduct(ray.direction(), ray.direction()) * ray.direction(); //sphere center projection on ray

    float l = sqrtf(powf(sphere_.radius(), 2) -
                    powf((sphere_.center() - proj).length(), 2));

    QVector3D r1 = proj + ray.direction() * l;
    QVector3D r2 = proj - ray.direction() * l;


    QVector3D point, normal;

//    if (sphere_.center().distanceToPoint(ray.origin()) < sphere_.radius())    //ray origin inside sphere
//    {
//        if (QVector3D::dotProduct(ray.direction(), r1 - ray.origin()) > 0)
//        {
//            point = r1;
//            normal = sphere_.center() - r1;
//        }
//        else
//        {
//            point = r2;
//            normal = sphere_.center() - r2;
//        }
//    }
//    else    //ray origin outside sphere
    {
        QVector3D c = (r1 - ray.origin()).length() < (r2 - ray.origin()).length() ? r1 : r2;

//        if (QVector3D::dotProduct(ray.direction(), c - ray.origin()) > 0)
        {
            point = c;
            normal = c - sphere_.center();
        }
//        else
//        {
//            return false;
//        }
    }

    collisionInfo = HCollision(point, normal, -ray.direction());
    return true;
}
