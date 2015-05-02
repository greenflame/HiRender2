#include "hboundingspherecollider.h"

HBoundingSphereCollider::HBoundingSphereCollider()
{

}

HBoundingSphereCollider::HBoundingSphereCollider(const HBoundingSphereCollider &collider)
{
    boundingSphere_ = collider.boundingSphere_;

    for (int i = 0; i < collider.colliders_.length(); i++)
        colliders_.append(collider.colliders_.at(i)->clone());
}

HBoundingSphereCollider::~HBoundingSphereCollider()
{
    for (int i = 0; i < colliders_.length(); i++)
        delete colliders_.at(i);
}

bool HBoundingSphereCollider::detectCollision(const HRay &ray, QVector3D &collisionPoint, ICollider **collider) const
{
    if (boundingSphere_.center().distanceToLine(ray.origin(), ray.direction()) > boundingSphere_.radius())
        return false;

    QVector3D closestCollision;
    ICollider *closestCollider;
    bool anyCollisions = false;

    for (int i = 0; i < colliders_.length(); i++)
    {
        QVector3D currentCollision;
        ICollider *currentCollider;
        if (colliders_.at(i)->detectCollision(ray, currentCollision, &currentCollider))
        {
            if (anyCollisions)
            {
                if (currentCollision.distanceToPoint(ray.origin()) < closestCollision.distanceToPoint(ray.origin()))
                {
                    closestCollision = currentCollision;
                    closestCollider = currentCollider;
                }
            }
            else
            {
                closestCollision = currentCollision;
                closestCollider = currentCollider;
                anyCollisions = true;
            }
        }
    }

    if (anyCollisions)
    {
        collisionPoint = closestCollision;
        *collider = closestCollider;
        return true;
    }

    return false;
}

bool HBoundingSphereCollider::processCollision(const HRay &ray, const HTracer3 &tracer, QColor &resultColor, QStack<IShader *> &shaderStack) const
{
    ICollider *collider;
    bool isCollisonExists = ICollider::detectCollision(ray, &collider);
    if (!isCollisonExists)
        return false;

    return collider->processCollision(ray, tracer, resultColor, shaderStack);
}

HSphere HBoundingSphereCollider::getBoundingSphere() const
{
    return boundingSphere_;
}

void HBoundingSphereCollider::transform(const QMatrix4x4 &m)
{
    for (int i = 0; i < colliders_.length(); i++)
        colliders_.at(i)->transform(m);

    boundingSphere_.setCenter(m * boundingSphere_.center());
}

ICollider *HBoundingSphereCollider::clone() const
{
    return new HBoundingSphereCollider(*this);
}

void HBoundingSphereCollider::addCollider(ICollider *collider)
{
    colliders_.append(collider);
    computeBoundingSphere();
}

void HBoundingSphereCollider::computeBoundingSphere()
{
    if (colliders_.length() == 1)
    {
        boundingSphere_ = colliders_[0]->getBoundingSphere();
        return;
    }

    if (colliders_.length() == 2)
    {
        HSphere s1 = colliders_[0]->getBoundingSphere();
        HSphere s2 = colliders_[1]->getBoundingSphere();

        float centerDistance = s1.center().distanceToPoint(s2.center());

        if (centerDistance < qAbs(s1.radius() - s2.radius()))  //one sphere is inside other
        {
            if (s1.radius() > s2.radius())
            {
                boundingSphere_ = s1;
                return;
            }
            else
            {
                boundingSphere_ = s2;
                return;
            }
        }
        else    // Spheres are not first insede second
        {
            float radius = (s1.radius() + s2.radius() + centerDistance) / 2;
            boundingSphere_.setCenter(s1.center() + (s2.center() - s1.center()).normalized() * (radius - s1.radius()));
            boundingSphere_.setRadius(radius);
            return;
        }
    }

    if (colliders_.length() > 2)
    {
        QVector3D center(0, 0, 0);
        float radius = 0;

        for (int i = 0; i < colliders_.length(); i++)
        {
            center += colliders_.at(i)->getBoundingSphere().center();
        }

        center /= colliders_.length();

        for (int i = 0; i < colliders_.length(); i++)
        {
            float currentRadius = colliders_.at(i)->getBoundingSphere().center().distanceToPoint(center) +
                    colliders_.at(i)->getBoundingSphere().radius();

            if (currentRadius > radius)
                radius = currentRadius;
        }

        boundingSphere_ = HSphere(center, radius);
        return;
    }
}
