//#include "htracer2.h"

//HTracer2::HTracer2(QObject *parent) : QObject(parent)
//{

//}

//HTracer2::~HTracer2()
//{

//}

//int HTracer2::render()
//{
//    resultImage_ = QImage(imageSize_, QImage::Format_RGB32);
//    resultImage_.fill(Qt::black);

//    renderedTilesMap_ = QImage(imageSize_.width() / tileSize_.width() + (imageSize_.width() % tileSize_.width() == 0 ? 0 : 1),
//                               imageSize_.height() / tileSize_.height() + (imageSize_.height() % tileSize_.height() == 0 ? 0 : 1),
//                               QImage::Format_RGB32);
//    renderedTilesMap_.fill(qRgb(0, 0, 0));

//    qsrand(QTime::currentTime().msec());

//    int totalTime = 0;

////    scene_.destructTree();
////    scene_.buildTree();

//    QRect tile;
//    while (getNextTile(tile))
//    {
//        QTime t;
//        t.start();
//        processTile(tile);
//        totalTime += t.elapsed();

//        QImage tmp = resultImage_;
//        QPainter painter(&tmp);
//        painter.setPen(Qt::red);
//        painter.drawRect(tile);

//        emit imageUpdate(tmp);
//    }

//    emit imageUpdate(resultImage_);
//    return totalTime;
//}

//bool HTracer2::getNextTile(QRect &tile)
//{
//    QPoint midleTile(renderedTilesMap_.width() / 2, renderedTilesMap_.height() / 2);
//    QPoint closestTile;
//    bool imageFinished = true;

//    for (int y = 0; y < renderedTilesMap_.height(); y++)
//        for (int x = 0; x < renderedTilesMap_.width(); x++)
//        {
//            QPoint currentTile(x, y);
//            if (renderedTilesMap_.pixel(currentTile) == qRgb(0,0,0))  //non rendered
//            {
//                if (imageFinished)
//                {
//                    imageFinished = false;
//                    closestTile = currentTile;
//                }
//                else
//                {
//                    if (length(midleTile, currentTile) < length(midleTile, closestTile))
//                    {
//                        closestTile = currentTile;
//                    }
//                }
//            }
//        }

//    if (imageFinished)
//        return false;

//    renderedTilesMap_.setPixel(closestTile, qRgb(0, 0, 1));

//    int x = closestTile.x() * tileSize_.width();
//    int y = closestTile.y() * tileSize_.height();

//    tile = QRect(x, y,
//                 qMin(tileSize_.width(), imageSize_.width() - x),
//                 qMin(tileSize_.height(), imageSize_.height() - y));
//    return true;
//}

//void HTracer2::processTile(const QRect &tile)
//{
//    for (int y = tile.top(); y < tile.top() + tile.height(); y++)
//        for(int x = tile.left(); x < tile.left() + tile.width(); x++)
//        {
//            processPixel(QPoint(x, y));
//        }
//}

//void HTracer2::processPixel(const QPoint &pixelPosition)
//{
//    HRay ray = matchRayForPixel(pixelPosition);
//    HCollision ci;
//    QColor resultColor = Qt::black;

//    if (findClosestCollision(ray, ci))
//    {
//        float lightness;
//        float lsl = qMin(lambertLightness(ci), shadowLightness(ci));
////        float ao = ambientOcclusion(ci, 250);
//        lightness = lsl/*ao * 0.5 + lsl * 0.5*/;
//        resultColor = mixColors(ci.material.diffuseColor, Qt::black, lightness, 1 - lightness);
//    }

//    resultImage_.setPixel(pixelPosition, resultColor.rgb());
//}

//HRay HTracer2::matchRayForPixel(const QPoint &pixelPosition)
//{
//    return HRay(QVector3D(0, 0, 0),
//                QVector3D(cameraFrustum_.left + (cameraFrustum_.right - cameraFrustum_.left) / imageSize_.width() * pixelPosition.x(),
//                          cameraFrustum_.bottom + (cameraFrustum_.top - cameraFrustum_.bottom)
//                                                                      / imageSize_.height() * (imageSize_.height() - pixelPosition.y() - 1),
//                          -cameraFrustum_.nearPlane));
//}

//bool HTracer2::findClosestCollision(const HRay &ray, HCollision &collisionInfo) const
//{
//    return scene_.treeHead()->detectCollision(ray, collisionInfo);
//}

//float HTracer2::length(const QPoint &p1, const QPoint &p2)
//{
//    float x = p1.x() - p2.x();
//    float y = p1.y() - p2.y();
//    return sqrt(x * x + y * y);
//}

//float HTracer2::lambertLightness(const HCollision &ci) const
//{
//    float maxLightness = 0;

//    for (int i = 0; i < scene_.lamps.length(); i++)
//    {
//        float currentLightness = qMax((float)0, QVector3D::dotProduct(ci.normal.normalized(), (scene_.lamps[i] - ci.point).normalized()));
//        maxLightness = qMax(maxLightness, currentLightness);
//    }

//    return maxLightness;
//}

//float HTracer2::ambientOcclusion(const HCollision &ci, int samples) const
//{
//    int intersectedRays = 0;

//    for (int i = 0; i < samples; i++)
//    {
//        QVector3D direction(-1 + qrand() / (double)RAND_MAX * 2.0,
//                         -1 + qrand() / (double)RAND_MAX * 2.0,
//                         -1 + qrand() / (double)RAND_MAX * 2.0);

//        if (QVector3D::dotProduct(direction, ci.normal) < 0)
//            direction = -direction;

//        HCollision tmpCi;
//        if (findClosestCollision(HRay(ci.point, direction), tmpCi))
//            intersectedRays++;
//    }

//    return 1 - (float)intersectedRays / samples;
//}

//float HTracer2::shadowLightness(const HCollision &ci) const
//{
//    for (int i = 0; i < scene_.lamps.length(); i++)
//    {
//        HCollision shadowRayCi;
//        if (findClosestCollision(HRay(ci.point, scene_.lamps[i] - ci.point), shadowRayCi))
//        {
//            if ((ci.point - shadowRayCi.point).length() > (ci.point - scene_.lamps[i]).length())
//            {
//                return 1;
//            }
//        }
//        else
//        {
//            return 1;
//        }
//    }

//    return 0;
//}

//QColor HTracer2::mixColors(const QColor &c1, const QColor &c2, float k1, float k2)
//{
//    return QColor((c1.red() * k1 + c2.red() * k2)/(k1 + k2),
//                  (c1.green() * k1 + c2.green() * k2)/(k1 + k2),
//                  (c1.blue() * k1 + c2.blue() * k2)/(k1 + k2));
//}

//HScene HTracer2::scene() const
//{
//    return scene_;
//}

//void HTracer2::setScene(const HScene &scene)
//{
//    scene_ = scene;
//}

//QSize HTracer2::imageSize() const
//{
//    return imageSize_;
//}

//void HTracer2::setImageSize(const QSize &imageSize)
//{
//    imageSize_ = imageSize;
//}
//HFrustum HTracer2::cameraFrustum() const
//{
//    return cameraFrustum_;
//}

//void HTracer2::setCameraFrustum(const HFrustum &cameraFrustum)
//{
//    cameraFrustum_ = cameraFrustum;
//}

//QSize HTracer2::tileSize() const
//{
//    return tileSize_;
//}

//void HTracer2::setTileSize(const QSize &tileSize)
//{
//    tileSize_ = tileSize;
//}
//QColor HTracer2::backgroundColor() const
//{
//    return backgroundColor_;
//}

//void HTracer2::setBackgroundColor(const QColor &backgroundColor)
//{
//    backgroundColor_ = backgroundColor;
//}





