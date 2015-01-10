#ifndef HSCENE_H
#define HSCENE_H

#include <QFile>

#include "hpolygon.h"

class HScene
{
public:
    HScene();
    ~HScene();

    void transform(const QMatrix4x4 &matrix);

    static QVector<HPolygon> loadObj(QString filename);

    QVector<HPolygon> polygons;
    QVector<QVector3D> lamps;
};

#endif // HSCENE_H
