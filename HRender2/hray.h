#ifndef HRAY_H
#define HRAY_H

#include <QVector3D>
#include <QMatrix4x4>

class HRay
{
public:
    HRay();
    HRay(const QVector3D &origin, const QVector3D &direction);
    ~HRay();

    void transform(const QMatrix4x4 &m);
    HRay transformed(const QMatrix4x4 &m) const;

    QVector3D origin() const;
    void setOrigin(const QVector3D &origin);

    QVector3D direction() const;
    void setDirection(const QVector3D &direction);

private:
    QVector3D origin_;
    QVector3D direction_;
};

#endif // HRAY_H
