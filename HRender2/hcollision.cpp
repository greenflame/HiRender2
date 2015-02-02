#include "hcollision.h"


HCollision::HCollision()
{

}

HCollision::HCollision(QVector3D point, QVector3D normal, QVector3D directionToEye, HMaterial *material)
{
    setPoint(point);
    setNormal(normal);
    setDirectionToEye(directionToEye);
    setMaterial(material);
}

HCollision::~HCollision()
{

}

QVector3D HCollision::point() const
{
    return point_;
}

void HCollision::setPoint(const QVector3D &point)
{
    point_ = point;
}

QVector3D HCollision::normal() const
{
    return normal_;
}

void HCollision::setNormal(const QVector3D &normal)
{
    normal_ = normal;
}

QVector3D HCollision::directionToEye() const
{
    return directionToEye_;
}

void HCollision::setDirectionToEye(const QVector3D &directionToEye)
{
    directionToEye_ = directionToEye;
}

HMaterial *HCollision::material() const
{
    return material_;
}

void HCollision::setMaterial(HMaterial *material)
{
    material_ = material;
}
