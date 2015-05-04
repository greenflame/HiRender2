/*
 * Base interface for all colliders.
 */

#ifndef ICOLLIDER_H
#define ICOLLIDER_H

#include <QVector3D>
#include <QMatrix4x4>
#include <QColor>
#include <QStack>

#include <shaders/ishader.h>

#include "hcollision.h"
#include "hray.h"
#include "hsphere.h"

class HTracer3;

class ICollider
{
public:
    virtual ~ICollider();

    /*
     * Input:
     * -ray
     *
     * Output:
     * -return [is collison exists]
     * -collision point [closest intersectino]
     * -collider [intersestion with..]
     */
    virtual bool detectCollision(const HRay &ray, QVector3D &collisionPoint, ICollider **collider) const = 0;
    virtual bool detectCollision(const HRay &ray, QVector3D &collisionPoint) const;
    virtual bool detectCollision(const HRay &ray, ICollider **collider) const;
    virtual bool detectCollision(const HRay &ray) const;

    /*
     * Input:
     * -ray
     * -tracer [for additional rays emiting]
     *
     * Output:
     * -return [collision exists]
     * -resultColor [result color of collision]
     */
    virtual bool processCollision(const HRay &ray, const HTracer3 &tracer, QColor &resultColor, QStack<IShader *> &shaderStack) const = 0;

    virtual HSphere getBoundingSphere() const = 0;
    virtual void transform(const QMatrix4x4 &m) = 0;
    virtual ICollider *clone() const = 0;
};

#endif // ICOLLIDER_H
