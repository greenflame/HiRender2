#ifndef ICOLLIDER_H
#define ICOLLIDER_H

#include <QVector3D>
#include <QColor>

#include "hcollision.h"
#include "hray.h"
#include "hmaterial.h"
#include "hsphere.h"
#include "ishader.h"

class HTracer3;

class ICollider
{
public:
    virtual ~ICollider();

    virtual bool detectCollision(const HRay &ray, QVector3D &collisionPoint, ICollider **collider) const = 0;
    virtual bool detectCollision(const HRay &ray, QVector3D &collisionPoint) const;
    virtual bool detectCollision(const HRay &ray, ICollider **collider) const;

    virtual bool processCollision(const HRay &ray, const HTracer3 &tracer, QColor &resultColor) const = 0;

    virtual HSphere getBoundingSphere() const = 0;
    virtual void transform(const QMatrix4x4 &m) = 0;
    virtual ICollider *clone() const = 0;
};

#endif // ICOLLIDER_H
