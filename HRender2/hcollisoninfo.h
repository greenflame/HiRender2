#ifndef HCOLLISONINFO_H
#define HCOLLISONINFO_H

#include <QVector3D>

#include "hmaterial.h"

class HCollisonInfo
{
public:
    HCollisonInfo() {}
    HCollisonInfo(QVector3D point, QVector3D normal, QVector3D directionToEye, HMaterial material)
        : point_(point), normal_(normal), directionToEye_(directionToEye), material_(material) {}

    QVector3D point() const;
    void setPoint(const QVector3D &value);

    QVector3D normal() const;
    void setNormal(const QVector3D &value);

    HMaterial material() const;
    void setMaterial(const HMaterial &material);

    QVector3D directionToEye() const;
    void setDirectionToEye(const QVector3D &directionToEye);

private:
    QVector3D point_;
    QVector3D normal_;
    QVector3D directionToEye_;
    HMaterial material_;

};

#endif // HCOLLISONINFO_H
