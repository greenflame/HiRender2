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
    void transform(const QMatrix4x4 &m);
    HModel transformed(const QMatrix4x4 &m) const;

    static HModel loadObj(QString filename);

    QVector<HPolygon> polygons;

};

#endif // HMODEL_H
