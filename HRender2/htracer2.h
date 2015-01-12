#ifndef HTRACER2_H
#define HTRACER2_H

#include <QObject>
#include <QImage>
#include <QPainter>
#include <QCoreApplication>
#include <QTime>

#include <math.h>

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
    bool getNextTile(QRect &tile);
    void processTile(const QRect &tile);
    void processPixel(const QPoint &pixelPosition);

    float lambertLightness(const HCollisonInfo &ci) const;
    bool isPointInShadow(const QVector3D point) const;

    //internal critical------
    HRay matchRayForPixel(const QPoint &pixelPosition);
    bool findClosestCollision(const HRay &ray, HCollisonInfo &collisionInfo) const;

    static float length(const QPoint &p1, const QPoint &p2);
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
    HFrustum cameraFrustum_;

    QSize imageSize_;
    QSize tileSize_;

    QImage resultImage_;
    QImage renderedTilesMap_;

};

#endif // HTRACER2_H
