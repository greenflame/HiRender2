#ifndef HMODEL_H
#define HMODEL_H

#include <QVector3D>
#include <QMatrix4x4>
#include <QVector>
#include <QFile>

#include <hpolygon.h>

class HModel
{
public:
    void transform(QMatrix4x4 m);
    HModel transformed(QMatrix4x4 m);

    static HModel loadObj(QString filename);

    QVector<HPolygon> polygons;

};

#endif // HMODEL_H
