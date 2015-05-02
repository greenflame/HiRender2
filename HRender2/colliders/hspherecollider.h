/*
 * Sphere collider.
 * !Bad intersection/normals detection algorithm.
 */

#ifndef HSPHERECOLLIDER_H
#define HSPHERECOLLIDER_H

#include <QVector3D>
#include <QMatrix4x4>

#include <cmath>
#include <algorithm>

#include "icollider.h"
#include "math/haccuracy.h"

class HSphereCollider : public ICollider
{
public:
    // Constructors
    HSphereCollider();
    HSphereCollider(HSphere sphere);
    HSphereCollider(HSphere sphere, IShader *shader);
    HSphereCollider(const HSphereCollider &collider);

    // ICollider interface
    bool detectCollision(const HRay &ray, QVector3D &collisionPoint, ICollider **collider) const;
    bool processCollision(const HRay &ray, const HTracer3 &tracer, QColor &resultColor, QStack<IShader *> &shaderStack) const;

    HSphere getBoundingSphere() const;
    ICollider *clone() const;
    void transform(const QMatrix4x4 &m);

    // Accesors
    HSphere sphere() const;
    void setSphere(const HSphere &sphere);

    IShader *shader() const;
    void setShader(IShader *shader);

private:
    bool localDetectCollision(const HRay &ray, HCollision &collisionInfo) const;

    HSphere sphere_;
    IShader *shader_;
};

#endif // HSPHERECOLLIDER_H
