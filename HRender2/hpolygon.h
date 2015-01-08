#ifndef HPOLYGON_H
#define HPOLYGON_H

#include <QVector3D>
#include <QMatrix4x4>
#include <QColor>

#include "hgeometry.h"

class HPolygon
{
public:
    HPolygon();
    HPolygon(QVector3D a, QVector3D b, QVector3D c);

    bool detectCollision(QVector3D rayOrigin, QVector3D rayDirecction, QVector3D &collisionPoint);

    void transform(QMatrix4x4 m);
    HPolygon transformed(QMatrix4x4 m);

    void generateColor();

    QVector3D a() const;
    void setA(const QVector3D &value);

    QVector3D b() const;
    void setB(const QVector3D &value);

    QVector3D c() const;
    void setC(const QVector3D &value);

    QColor getColor() const;
    void setColor(const QColor &value);

private:
    QVector3D av, bv, cv;
    QColor color;

};

#endif // HPOLYGON_H
