#ifndef HCOLLISION_H
#define HCOLLISION_H

#include <QVector3D>

class HCollision
{
public:
    HCollision();
    HCollision(QVector3D point, QVector3D normal, QVector3D directionToEye);
    ~HCollision();

    QVector3D point() const;
    void setPoint(const QVector3D &point);

    QVector3D normal() const;
    void setNormal(const QVector3D &normal);

    QVector3D directionToEye() const;
    void setDirectionToEye(const QVector3D &directionToEye);

private:
    QVector3D point_;
    QVector3D normal_;
    QVector3D directionToEye_;
};

#endif // HCOLLISONINFO_H
