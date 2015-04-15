#include "icollider.h"


ICollider::~ICollider()
{

}

bool ICollider::detectCollision(const HRay &ray, QVector3D &collisionPoint) const
{
    ICollider *tmp;
    return detectCollision(ray, collisionPoint, &tmp);
}

bool ICollider::detectCollision(const HRay &ray, ICollider **collider) const
{
    QVector3D tmp;
    return detectCollision(ray, tmp, collider);
}
