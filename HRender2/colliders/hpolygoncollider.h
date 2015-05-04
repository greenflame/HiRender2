/*
 * Polygon collider.
 * !Unoptimal boundin sphere computing.
 * !Unfinished textures mapping.
 */

#ifndef HPOLYGONCOLLIDER_H
#define HPOLYGONCOLLIDER_H

// Base interface
#include "colliders/icollider.h"

class HPolygonCollider : public ICollider
{
public:
    // Constructors
    HPolygonCollider();
    HPolygonCollider(QVector3D v1, QVector3D v2, QVector3D v3, IShader *shader);
    HPolygonCollider(const HPolygonCollider &collider);

    // ICollider interface
    bool detectCollision(const HRay &ray, QVector3D &collisionPoint, ICollider **collider) const;
    bool processCollision(const HRay &ray, const HTracer3 &tracer, QColor &resultColor, QStack<IShader *> &shaderStack) const;

    HSphere getBoundingSphere() const;
    void transform(const QMatrix4x4 &m);
    ICollider *clone() const;

    // Accesors
    QVector3D v1() const;
    void setV1(const QVector3D &value);

    QVector3D v2() const;
    void setV2(const QVector3D &value);

    QVector3D v3() const;
    void setV3(const QVector3D &value);

    QVector3D n1() const;
    void setN1(const QVector3D &n1);

    QVector3D n2() const;
    void setN2(const QVector3D &n2);

    QVector3D n3() const;
    void setN3(const QVector3D &n3);

    QVector3D t1() const;
    void setT1(const QVector3D &t1);

    QVector3D t2() const;
    void setT2(const QVector3D &t2);

    QVector3D t3() const;
    void setT3(const QVector3D &t3);

    IShader *shader() const;
    void setShader(IShader *shader);

    QImage *texture() const;
    void setTexture(QImage *value);

    bool useNormals() const;
    void setUseNormals(bool useNormals);

    bool useTexture() const;
    void setUseTexture(bool useTexture);

private:
    QVector3D v1_, v2_, v3_;
    QVector3D n1_, n2_, n3_;
    QVector3D t1_, t2_, t3_;
    IShader *shader_;
    QImage *texture_;

    void computeBoundingSphere();

    bool useNormals_;
    bool useTexture_;

    QVector3D computeNormal(const HRay &ray, const QVector3D &collisionPoint) const;

};

#endif // HPOLYGONCOLLIDER_H
