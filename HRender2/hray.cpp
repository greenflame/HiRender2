#include "hray.h"


HRay::HRay()
{

}

HRay::HRay(const QVector3D &origin, const QVector3D &direction)
{
    setOrigin(origin);
    setDirection(direction);
}

HRay::~HRay()
{

}

QVector3D HRay::origin() const
{
    return origin_;
}

void HRay::setOrigin(const QVector3D &origin)
{
    origin_ = origin;
}

QVector3D HRay::direction() const
{
    return direction_;
}

void HRay::setDirection(const QVector3D &direction)
{
    direction_ = direction;
}
