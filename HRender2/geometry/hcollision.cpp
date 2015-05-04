#include "hcollision.h"


HCollision::HCollision()
{

}

HCollision::HCollision(QVector3D point, QVector3D normal, QVector3D directionToEye)
{
    setPoint(point);
    setNormal(normal);
    setDirectionToEye(directionToEye);
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
    normal_ = normal.normalized();
}

QVector3D HCollision::directionToEye() const
{
    return directionToEye_;
}

void HCollision::setDirectionToEye(const QVector3D &directionToEye)
{
    directionToEye_ = directionToEye;
}
