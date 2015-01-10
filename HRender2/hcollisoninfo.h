#ifndef HCOLLISONINFO_H
#define HCOLLISONINFO_H

#include <QVector3D>

#include "hmaterial.h"

class HCollisonInfo
{
public:
    HCollisonInfo() {}
    HCollisonInfo(QVector3D point, QVector3D normal, QVector3D rayDirection, HMaterial material)
        : point_(point), normal_(normal), rayDirection_(rayDirection), material_(material) {}

    QVector3D point() const;
    void setPoint(const QVector3D &value);

    QVector3D normal() const;
    void setNormal(const QVector3D &value);

    QVector3D rayDirection() const;
    void setRayDirection(const QVector3D &value);

    HMaterial material() const;
    void setMaterial(const HMaterial &material);

private:
    QVector3D point_;
    QVector3D normal_;
    QVector3D rayDirection_;
    HMaterial material_;

};

#endif // HCOLLISONINFO_H
