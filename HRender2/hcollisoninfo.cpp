#include "hcollisoninfo.h"


QVector3D HCollisonInfo::point() const
{
    return point_;
}

void HCollisonInfo::setPoint(const QVector3D &value)
{
    point_ = value;
}

QVector3D HCollisonInfo::normal() const
{
    return normal_;
}

void HCollisonInfo::setNormal(const QVector3D &value)
{
    normal_ = value;
}

HMaterial HCollisonInfo::material() const
{
    return material_;
}

void HCollisonInfo::setMaterial(const HMaterial &material)
{
    material_ = material;
}

QVector3D HCollisonInfo::directionToEye() const
{
    return directionToEye_;
}

void HCollisonInfo::setDirectionToEye(const QVector3D &directionToEye)
{
    directionToEye_ = directionToEye;
}





