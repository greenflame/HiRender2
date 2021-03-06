/*
 * Frustum container. Consist of:
 * -left, right, bottom, top border
 * -near, far plane
 */

#ifndef HFRUSTUM_H
#define HFRUSTUM_H


class HFrustum
{
public:
    HFrustum();
    HFrustum(float left, float right, float bottom, float top, float nearPlane, float farPlane);
    ~HFrustum();

    float left() const;
    void setLeft(float left);

    float right() const;
    void setRight(float right);

    float bottom() const;
    void setBottom(float bottom);

    float top() const;
    void setTop(float top);

    float nearPlane() const;
    void setNearPlane(float nearPlane);

    float farPlane() const;
    void setFarPlane(float farPlane);

private:
    float left_;
    float right_;
    float bottom_;
    float top_;
    float nearPlane_;
    float farPlane_;
};

#endif // HFRUSTUM_H
