/*
 * Bounding sphere represents set of colliders as one collider.
 */

#ifndef HBOUNDINGSPHERECOLLIDER_H
#define HBOUNDINGSPHERECOLLIDER_H

#include <QVector>

#include "colliders/icollider.h"    // Base interface

class HBoundingSphereCollider : public ICollider
{
public:
    HBoundingSphereCollider();
    HBoundingSphereCollider(const HBoundingSphereCollider &collider);
    ~HBoundingSphereCollider();

    /*
     * ICollider interface functions
     */
    bool detectCollision(const HRay &ray, QVector3D &collisionPoint, ICollider **collider) const;
    bool processCollision(const HRay &ray, const HTracer3 &tracer, QColor &resultColor, QStack<IShader *> &shaderStack) const;

    HSphere getBoundingSphere() const;
    void transform(const QMatrix4x4 &m);
    ICollider *clone() const;

    /*
     * Add collider to list and resolbe bounding sphere.
     */
    void addCollider(ICollider *collider);

private:
    void computeBoundingSphere();

    QVector<ICollider *> colliders_;
    HSphere boundingSphere_;
};

#endif // HBOUNDINGSPHERECOLLIDER_H
