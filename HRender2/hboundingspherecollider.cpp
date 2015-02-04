#include "hboundingspherecollider.h"

HBoundingSphereCollider::HBoundingSphereCollider()
{

}

HBoundingSphereCollider::HBoundingSphereCollider(const HBoundingSphereCollider &collider)
{
    center_ = collider.center_;
    radius_ = collider.radius_;

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
    if (center_.distanceToLine(ray.origin(), ray.direction()) > radius_)
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

bool HBoundingSphereCollider::processCollision(const HRay &ray, const HTracer3 &tracer, QColor &resultColor) const
{
    ICollider *collider;
    bool isCollisonExists = ICollider::detectCollision(ray, &collider);
    if (!isCollisonExists)
        return false;

    return collider->processCollision(ray, tracer, resultColor);
}

HSphere HBoundingSphereCollider::getBoundingSphere() const
{
    return HSphere(center_, radius_);
}

void HBoundingSphereCollider::transform(const QMatrix4x4 &m)
{
    for (int i = 0; i < colliders_.length(); i++)
        colliders_.at(i)->transform(m);

    center_ = m * center_;
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
        center_ = colliders_[0]->getBoundingSphere().center();
        radius_ = colliders_[0]->getBoundingSphere().radius();
        return;
    }

    if (colliders_.length() == 2)
    {
        HSphere s1 = colliders_[0]->getBoundingSphere();
        HSphere s2 = colliders_[1]->getBoundingSphere();

        float centerDistance = s1.center().distanceToPoint(s2.center());

        if (centerDistance < qAbs(s1.radius() - s2.radius()))  //one sphere inside the other
        {
            if (s1.radius() > s2.radius())
            {
                center_ = s1.center();
                radius_ = s1.radius();
                return;
            }
            else
            {
                center_ = s2.center();
                radius_ = s2.radius();
                return;
            }
        }
        else    //spheres are not first insede second
        {
            float radius = (s1.radius() + s2.radius() + centerDistance) / 2;
            center_ = s1.center() + (s2.center() - s1.center()).normalized() * (radius - s1.radius());
            radius_ = radius;
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

        center_ = center;
        radius_ = radius;
        return;
    }
}
