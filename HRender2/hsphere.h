/*
 * Sphere container. Consist of:
 * -center
 * -radius
 */

#ifndef HSPHERE_H
#define HSPHERE_H

#include <QVector3D>

class HSphere
{
public:
    HSphere();
    HSphere(QVector3D center, float radius);
    ~HSphere();

    QVector3D center() const;
    void setCenter(const QVector3D &center);

    float radius() const;
    void setRadius(float radius);

private:
    QVector3D center_;
    float radius_;
};

#endif // HSPHERE_H
