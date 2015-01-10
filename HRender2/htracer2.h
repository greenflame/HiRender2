#ifndef HTRACER2_H
#define HTRACER2_H

#include <QObject>
#include <QImage>

#include "hfrustum.h"
#include "hpolygon.h"
#include "hscene.h"

class HTracer2 : public QObject
{
    Q_OBJECT
public:
    explicit HTracer2(QObject *parent = 0);
    ~HTracer2();

    void render();

    //unind
    QImage traceRays(int imageHeight, int imageWidth, float left, float right, float bottom, float top, float nearPlane/*, float farPlane*/);
    QColor traceRay(const QVector3D &rayOrigin, const QVector3D &rayDirecction);

    bool findClosestCollision(const QVector3D &rayOrigin, const QVector3D &rayDirecction, HCollisonInfo &collisionInfo) const;

    float lambertLightness(const HCollisonInfo &ci) const;
    bool isPointInShadow(const QVector3D point) const;

    static QColor mixColors(const QColor &c1, const QColor &c2, float k1, float k2);


    //getters/setters------
    HScene scene() const;
    void setScene(const HScene &scene);

    QSize imageSize() const;
    void setImageSize(const QSize &imageSize);

    HFrustum cameraFrustum() const;
    void setCameraFrustum(const HFrustum &cameraFrustum);

    QSize tileSize() const;
    void setTileSize(const QSize &tileSize);

signals:
    void imageUpdate(QImage newImage);

public slots:

private:
    HScene scene_;

    QSize imageSize_;
    HFrustum cameraFrustum_;

    QSize tileSize_;

    QImage resultImage_;

};

#endif // HTRACER2_H
