#include "htracer.h"


QImage HTracer::traceRays(int imageWidth, int imageHeight, float left, float right, float bottom, float top, float nearPlane/*, float farPlane*/)
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

QColor HTracer::traceRay(const QVector3D &rayOrigin, const QVector3D &rayDirecction)
{
    HCollisonInfo ci;
    if (!findClosestCollision(rayOrigin, rayDirecction, ci))
        return Qt::white;

    float lightness;
    lightness = isPointInShadow(ci.point()) ? 0 : lambertLightness(ci);

    return mixColors(ci.material().diffuseColor(), Qt::black, lightness, 1 - lightness);
}

bool HTracer::findClosestCollision(const QVector3D &rayOrigin, const QVector3D &rayDirecction, HCollisonInfo &collisionInfo) const
{
    HCollisonInfo closestCollision;
    bool anyCollisions = false;

    for (int i = 0; i < polygons.length(); i++)
    {
        HCollisonInfo currentCollision;
        bool updateCollisionInfo = false;

        if (polygons[i].detectCollision(rayOrigin, rayDirecction, currentCollision))
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

float HTracer::lambertLightness(const HCollisonInfo &ci) const
{
    return qMax((float)0, QVector3D::dotProduct(ci.normal().normalized(), (lamp - ci.point()).normalized()));
}

bool HTracer::isPointInShadow(const QVector3D point) const
{
    for (int i = 0; i < polygons.length(); i++)
        if (HGeometry::isIntersectedIntervalPolygon(point, lamp,
                                                    polygons[i].a(),
                                                    polygons[i].b(),
                                                    polygons[i].c()))
            return true;
    return false;
}

QColor HTracer::mixColors(const QColor &c1, const QColor &c2, float k1, float k2)
{
    return QColor((c1.red() * k1 + c2.red() * k2)/(k1 + k2),
                  (c1.green() * k1 + c2.green() * k2)/(k1 + k2),
                  (c1.blue() * k1 + c2.blue() * k2)/(k1 + k2));
}
