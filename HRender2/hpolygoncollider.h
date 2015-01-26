#ifndef HPOLYGONCOLLIDER_H
#define HPOLYGONCOLLIDER_H

#include <QVector3D>
#include <QMatrix4x4>
#include <QColor>

#include "icollider.h"
#include "hcollision.h"
#include "hmaterial.h"
#include "haccuracy.h"

class HPolygonCollider : public ICollider
{
public:
    // Constructors
    HPolygonCollider();
    HPolygonCollider(QVector3D a, QVector3D b, QVector3D c);
    HPolygonCollider(QVector3D a, QVector3D b, QVector3D c, HMaterial material);
    HPolygonCollider(const HPolygonCollider &collider);

    // ICollider interface
    bool detectCollision(const HRay &ray, HCollision &collisionInfo) const;
    HSphere getBoundingSphere() const;
    void transform(const QMatrix4x4 &m);
    ICollider *clone() const;

    // Accesors
    QVector3D a() const;
    void setA(const QVector3D &value);

    QVector3D b() const;
    void setB(const QVector3D &value);

    QVector3D c() const;
    void setC(const QVector3D &value);

    HMaterial material() const;
    void setMaterial(HMaterial material);

private:
    QVector3D a_, b_, c_;
    HMaterial material_;
};

#endif // HPOLYGONCOLLIDER_H
