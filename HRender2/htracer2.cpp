#include "htracer2.h"

HTracer2::HTracer2(QObject *parent) : QObject(parent)
{

}

HTracer2::~HTracer2()
{

}

void HTracer2::render()
{
    resultImage_ = traceRays(imageSize_.width(), imageSize_.height(),
                            cameraFrustum_.left(),
                            cameraFrustum_.right(),
                            cameraFrustum_.bottom(),
                            cameraFrustum_.top(),
                            cameraFrustum_.nearPlane());

    emit imageUpdate(resultImage_);
}

QImage HTracer2::traceRays(int imageWidth, int imageHeight, float left, float right, float bottom, float top, float nearPlane/*, float farPlane*/)
{
    QImage img(imageWidth, imageHeight, QImage::Format_RGB32);

    for (int i = 0; i < imageHeight; i++)
        for(int j = 0; j < imageWidth; j++)
        {
            QVector3D rayOrigin(0, 0, 0);
            QVector3D rayDirection(left + (right - left)/(double)imageWidth*(double)j,
                                   bottom + (top - bottom)/(double)imageHeight*(double)i,
                                   -nearPlane);
            img.setPixel(j, imageHeight - i - 1, traceRay(rayOrigin, rayDirection).rgb());
        }
    return img;
}

QColor HTracer2::traceRay(const QVector3D &rayOrigin, const QVector3D &rayDirecction)
{
    HCollisonInfo ci;
    if (!findClosestCollision(rayOrigin, rayDirecction, ci))
        return Qt::white;

    float lightness;
    lightness = isPointInShadow(ci.point()) ? 0 : lambertLightness(ci);

    return mixColors(ci.material().diffuseColor(), Qt::black, lightness, 1 - lightness);
}

bool HTracer2::findClosestCollision(const QVector3D &rayOrigin, const QVector3D &rayDirecction, HCollisonInfo &collisionInfo) const
{
    HCollisonInfo closestCollision;
    bool anyCollisions = false;

    for (int i = 0; i < scene_.polygons.length(); i++)
    {
        HCollisonInfo currentCollision;
        bool updateCollisionInfo = false;

        if (scene_.polygons[i].detectCollision(rayOrigin, rayDirecction, currentCollision))
        {
            if (anyCollisions)
            {
                if ((rayOrigin - currentCollision.point()).length() < (rayOrigin - closestCollision.point()).length())
                {
                    updateCollisionInfo = true;
                }
            }
            else
            {
                anyCollisions = true;
                updateCollisionInfo = true;
            }
        }

        if (updateCollisionInfo)
        {
            closestCollision = currentCollision;
        }
    }

    if (anyCollisions)
    {
        collisionInfo = closestCollision;
        return true;
    }

    return false;
}

float HTracer2::lambertLightness(const HCollisonInfo &ci) const //!!!!!
{
    float maxLightness = 0;

    for (int i = 0; i < scene_.lamps.length(); i++)
    {
        float currentLightness = qMax((float)0, QVector3D::dotProduct(ci.normal().normalized(), (scene_.lamps[0] - ci.point()).normalized()));
        maxLightness = qMax(maxLightness, currentLightness);
    }

    return maxLightness;
}

bool HTracer2::isPointInShadow(const QVector3D point) const //!!!!!
{
    for (int i = 0; i < scene_.polygons.length(); i++)
        if (HGeometry::isIntersectedIntervalPolygon(point, scene_.lamps[0],
                                                    scene_.polygons[i].a(),
                                                    scene_.polygons[i].b(),
                                                    scene_.polygons[i].c()))
            return true;
    return false;
}

QColor HTracer2::mixColors(const QColor &c1, const QColor &c2, float k1, float k2)
{
    return QColor((c1.red() * k1 + c2.red() * k2)/(k1 + k2),
                  (c1.green() * k1 + c2.green() * k2)/(k1 + k2),
                  (c1.blue() * k1 + c2.blue() * k2)/(k1 + k2));
}
HScene HTracer2::scene() const
{
    return scene_;
}

void HTracer2::setScene(const HScene &scene)
{
    scene_ = scene;
}
QSize HTracer2::imageSize() const
{
    return imageSize_;
}

void HTracer2::setImageSize(const QSize &imageSize)
{
    imageSize_ = imageSize;
}
HFrustum HTracer2::cameraFrustum() const
{
    return cameraFrustum_;
}

void HTracer2::setCameraFrustum(const HFrustum &cameraFrustum)
{
    cameraFrustum_ = cameraFrustum;
}
QSize HTracer2::tileSize() const
{
    return tileSize_;
}

void HTracer2::setTileSize(const QSize &tileSize)
{
    tileSize_ = tileSize;
}




