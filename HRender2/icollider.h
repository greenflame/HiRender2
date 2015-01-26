#ifndef ICOLLIDER_H
#define ICOLLIDER_H

#include <QVector3D>

#include "hcollision.h"
#include "hray.h"
#include "hmaterial.h"
#include "hsphere.h"

class ICollider
{
public:
    virtual ~ICollider();

    virtual bool detectCollision(const HRay &ray, HCollision &collisionInfo) const = 0;
    virtual HSphere getBoundingSphere() const = 0;
    virtual void transform(const QMatrix4x4 &m) = 0;
    virtual ICollider *clone() const = 0;
};

#endif // ICOLLIDER_H
