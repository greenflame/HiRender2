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

void HRay::transform(const QMatrix4x4 &m)
{
    QVector4D originTmp(origin_, 1);
    setOrigin(QVector3D(m * originTmp));

    QVector4D directionTmp(direction_, 0);
    setDirection(QVector3D(m * directionTmp));
}

HRay HRay::transformed(const QMatrix4x4 &m) const
{
    HRay tmp = *this;
    tmp.transform(m);
    return tmp;
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
    direction_ = direction.normalized();
}
