#ifndef HSPHERECOLLIDER_H
#define HSPHERECOLLIDER_H

#include <QVector3D>
#include <QMatrix4x4>

#include <cmath>
#include <algorithm>

#include "icollider.h"
#include "haccuracy.h"

class HSphereCollider : public ICollider
{
public:
    // Constructors
    HSphereCollider();
    HSphereCollider(QVector3D center, float radius);
    HSphereCollider(QVector3D center, float radius, IShader *shader);
    HSphereCollider(const HSphereCollider &collider);

    // ICollider interface
    bool detectCollision(const HRay &ray, QVector3D &collisionPoint, ICollider **collider) const;
    bool processCollision(const HRay &ray, const HTracer3 &tracer, QColor &resultColor) const;

    HSphere getBoundingSphere() const;
    ICollider *clone() const;
    void transform(const QMatrix4x4 &m);

    // Accesors
    QVector3D center() const;
    void setCenter(const QVector3D &center);

    float radius() const;
    void setRadius(float radius);

    IShader *shader() const;
    void setShader(IShader *shader);

private:
    bool localDetectCollision(const HRay &ray, HCollision &collisionInfo) const;

    QVector3D center_;
    float radius_;
    IShader *shader_;
};

#endif // HSPHERECOLLIDER_H
