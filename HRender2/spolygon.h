#ifndef SPOLYGON_H
#define SPOLYGON_H

#include <QString>
#include <QVector3D>

class SPolygon
{
public:
    SPolygon();
    SPolygon(const QVector3D &v1, const QVector3D &v2, const QVector3D &v3, const QString &materialName);
    SPolygon(const QVector3D &v1, const QVector3D &v2, const QVector3D &v3,
             const QVector3D &n1, const QVector3D &n2, const QVector3D &n3, const QString &materialName);
    ~SPolygon();

    QVector3D v1() const;
    void setV1(const QVector3D &v1);

    QVector3D v2() const;
    void setV2(const QVector3D &v2);

    QVector3D v3() const;
    void setV3(const QVector3D &v3);

    QVector3D n1() const;
    void setN1(const QVector3D &n1);

    QVector3D n2() const;
    void setN2(const QVector3D &n2);

    QVector3D n3() const;
    void setN3(const QVector3D &n3);

    bool useNormals() const;
    void setUseNormals(bool useNormals);

    QString materialName() const;
    void setMaterialName(const QString &materialName);

private:
    QVector3D v1_, v2_, v3_;
    QVector3D n1_, n2_, n3_;
    bool useNormals_;

    QString materialName_;
};

#endif // SPOLYGON_H
