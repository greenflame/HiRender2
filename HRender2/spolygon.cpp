#include "spolygon.h"

SPolygon::SPolygon()
{
    setUseNormals(false);
}

SPolygon::SPolygon(const QVector3D &v1, const QVector3D &v2, const QVector3D &v3, const QString &materialName)
{
    setV1(v1);
    setV2(v2);
    setV3(v3);

    setUseNormals(false);
    setMaterialName(materialName);
}

SPolygon::SPolygon(const QVector3D &v1, const QVector3D &v2, const QVector3D &v3,
                   const QVector3D &n1, const QVector3D &n2, const QVector3D &n3,
                   const QString &materialName)
{
    setV1(v1);
    setV2(v2);
    setV3(v3);

    setN1(n1);
    setN2(n2);
    setN3(n3);

    setUseNormals(true);
    setMaterialName(materialName);
}

SPolygon::~SPolygon()
{

}

QVector3D SPolygon::v1() const
{
    return v1_;
}

void SPolygon::setV1(const QVector3D &v1)
{
    v1_ = v1;
}

QVector3D SPolygon::v2() const
{
    return v2_;
}

void SPolygon::setV2(const QVector3D &v2)
{
    v2_ = v2;
}

QVector3D SPolygon::v3() const
{
    return v3_;
}

void SPolygon::setV3(const QVector3D &v3)
{
    v3_ = v3;
}

QVector3D SPolygon::n1() const
{
    return n1_;
}

void SPolygon::setN1(const QVector3D &n1)
{
    n1_ = n1;
}

QVector3D SPolygon::n2() const
{
    return n2_;
}

void SPolygon::setN2(const QVector3D &n2)
{
    n2_ = n2;
}

QVector3D SPolygon::n3() const
{
    return n3_;
}

void SPolygon::setN3(const QVector3D &n3)
{
    n3_ = n3;
}

bool SPolygon::useNormals() const
{
    return useNormals_;
}

void SPolygon::setUseNormals(bool useNormals)
{
    useNormals_ = useNormals;
}

QString SPolygon::materialName() const
{
    return materialName_;
}

void SPolygon::setMaterialName(const QString &materialName)
{
    materialName_ = materialName;
}



