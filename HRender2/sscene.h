#ifndef SSCENE_H
#define SSCENE_H

#include <QDebug>

#include <QFileInfo>
#include <QVector>
#include <QVector3D>
#include <QMap>
#include <QString>
#include <QFile>

#include <spolygon.h>
#include <smaterial.h>
#include <htracer3.h>

class SScene
{
public:
    SScene();
    ~SScene();

    QVector<SPolygon> polygons;
    QMap<QString, SMaterial> materials;
    QVector<QVector3D> lights;

    void clear();
    bool loadObj(const QString &fileName);

    void copyToTracer(HTracer3 &tracer);
    void copyToTracer(HTracer3 &tracer, const QString &shader);

private:
    bool loadMtl(const QString &fileName);

};

#endif // SSCENE_H
