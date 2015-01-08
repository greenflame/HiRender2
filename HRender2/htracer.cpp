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
            img.setPixel(j, imageWidth - i - 1, traceRay(rayOrigin, rayDirection).rgb());
        }
    return img;
}

QColor HTracer::traceRay(QVector3D rayOrigin, QVector3D rayDirecction)
{
    for (int i = 0; i < polygons.length(); i++)
    {
        QVector3D ip;
        if (polygons[i].detectCollision(rayOrigin, rayDirecction, ip))
            return polygons[i].getColor();
    }

    return Qt::white;
}
