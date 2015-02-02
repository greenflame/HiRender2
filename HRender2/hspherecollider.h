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
    HSphereCollider(QVector3D center, float radius, HMaterial *material);
    HSphereCollider(const HSphereCollider &collider);

    // ICollider interface
    bool detectCollision(const HRay &ray, HCollision &collisionInfo) const;
    HSphere getBoundingSphere() const;

    ICollider *clone() const;
    void transform(const QMatrix4x4 &m);    //!!!scale

    // Accesors
    QVector3D center() const;
    void setCenter(const QVector3D &center);

    float radius() const;
    void setRadius(float radius);

    HMaterial *material() const;
    void setMaterial(HMaterial *material);

private:
    QVector3D center_;
    float radius_;
    HMaterial *material_;
};

#endif // HSPHERECOLLIDER_H
