#ifndef HBOUNDINGSPHERECOLLIDER_H
#define HBOUNDINGSPHERECOLLIDER_H

#include <QVector>

#include "icollider.h"
#include "hsphere.h"

class HBoundingSphereCollider : public ICollider
{
public:
    HBoundingSphereCollider();
    HBoundingSphereCollider(const HBoundingSphereCollider &collider);
    ~HBoundingSphereCollider();

    // ICollider interface
    bool detectCollision(const HRay &ray, QVector3D &collisionPoint, ICollider **collider) const;
    bool processCollision(const HRay &ray, const HTracer3 &tracer, QColor &resultColor) const;

    HSphere getBoundingSphere() const;
    void transform(const QMatrix4x4 &m);
    ICollider *clone() const;

    // Collider functions
    void addCollider(ICollider *collider);

private:
    void computeBoundingSphere();
    QVector<ICollider *> colliders_;

    QVector3D center_;
    float radius_;
};

#endif // HBOUNDINGSPHERECOLLIDER_H
