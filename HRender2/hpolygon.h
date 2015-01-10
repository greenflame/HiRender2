#ifndef HPOLYGON_H
#define HPOLYGON_H

#include <QVector3D>
#include <QMatrix4x4>
#include <QColor>

#include "hgeometry.h"
#include "hcollisoninfo.h"
#include "hmaterial.h"

class HPolygon
{
public:
    HPolygon();
    HPolygon(QVector3D a, QVector3D b, QVector3D c);

    bool detectCollision(const QVector3D &rayOrigin, const QVector3D &rayDirecction, HCollisonInfo &collisionInfo) const;

    void transform(const QMatrix4x4 &m);
    HPolygon transformed(const QMatrix4x4 &m) const;

    void generateColor();

    QVector3D a() const;
    void setA(const QVector3D &value);

    QVector3D b() const;
    void setB(const QVector3D &value);

    QVector3D c() const;
    void setC(const QVector3D &value);

    HMaterial material() const;
    void setMaterial(const HMaterial &material);

private:
    QVector3D a_, b_, c_;
    HMaterial material_;

};

#endif // HPOLYGON_H
