#include "hlibrary.h"

HLibrary::HLibrary()
{

}

HLibrary::~HLibrary()
{

}

QVector3D HLibrary::projectPointOnLine(QVector3D l1, QVector3D l2, QVector3D p)
{
    QVector3D lineDirection = l2 - l1;
    QVector3D v = p - l1;
    return l1 + QVector3D::dotProduct(v, lineDirection)
            / QVector3D::dotProduct(lineDirection, lineDirection) * lineDirection;
}

QVector3D HLibrary::reflectRay(QVector3D ray, QVector3D normal)
{
    QVector3D inplaneVector = QVector3D::crossProduct(ray, normal);
    QVector3D rayProjection = QVector3D::crossProduct(normal, inplaneVector);

    QVector3D pointProjection = projectPointOnLine(QVector3D(0, 0, 0), rayProjection, ray);

    QVector3D translateVector = pointProjection - ray;

    return ray + translateVector * 2;
}
