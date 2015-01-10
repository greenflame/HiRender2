#include "hfrustum.h"

float HFrustum::left() const
{
    return left_;
}

void HFrustum::setLeft(float left)
{
    left_ = left;
}

float HFrustum::right() const
{
    return right_;
}

void HFrustum::setRight(float right)
{
    right_ = right;
}

float HFrustum::bottom() const
{
    return bottom_;
}

void HFrustum::setBottom(float bottom)
{
    bottom_ = bottom;
}

float HFrustum::top() const
{
    return top_;
}

void HFrustum::setTop(float top)
{
    top_ = top;
}

float HFrustum::nearPlane() const
{
    return nearPlane_;
}

void HFrustum::setNearPlane(float nearPlane)
{
    nearPlane_ = nearPlane;
}

float HFrustum::farPlane() const
{
    return farPlane_;
}

void HFrustum::setFarPlane(float farPlane)
{
    farPlane_ = farPlane;
}
