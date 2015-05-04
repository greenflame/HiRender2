#include "hsphere.h"

HSphere::HSphere()
{

}

HSphere::HSphere(QVector3D center, float radius)
{
    setCenter(center);
    setRadius(radius);
}

HSphere::~HSphere()
{

}

QVector3D HSphere::center() const
{
    return center_;
}

void HSphere::setCenter(const QVector3D &center)
{
    center_ = center;
}

float HSphere::radius() const
{
    return radius_;
}

void HSphere::setRadius(float radius)
{
    radius_ = radius;
}



