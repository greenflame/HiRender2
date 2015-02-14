#ifndef SSCENE_H
#define SSCENE_H

#include <QVector>
#include <QVector3D>
#include <QMap>
#include <QString>

#include <spolygon.h>
#include <smaterial.h>

class SScene
{
public:
    SScene();
    ~SScene();

    QVector<SPolygon> polygons;
    QMap<QString, SMaterial> materials;
    QVector<QVector3D> lights;

    void loadObj(const QString &fileName);

private:
    void loadMtl(const QString &filename);

};

#endif // SSCENE_H
