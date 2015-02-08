#ifndef HLIBRARY_H
#define HLIBRARY_H

#include "qvector3d.h"

class HLibrary
{
public:
    HLibrary();
    ~HLibrary();

    static QVector3D projectPointOnLine(QVector3D l1, QVector3D l2, QVector3D p);
    static QVector3D reflectRay(QVector3D ray, QVector3D normal);
};

#endif // HLIBRARY_H
