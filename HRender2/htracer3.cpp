#include "htracer3.h"

HTracer3::HTracer3(QObject *parent) : QObject(parent)
{
    setCameraFrustum(HFrustum(-0.9, 0.9, -0.5, 0.5, 1, 1000));
    setImageSize(QSize(1280, 720));
    setTileSize(QSize(128, 128));
    setBackgroundColor(Qt::black);

    addMaterial("default", Qt::gray);
}

HTracer3::~HTracer3()
{
    deleteColliders();
}

QImage HTracer3::render()
{
    QTime timer;

    QImage resultImage(imageSize(), QImage::Format_ARGB32);
    resultImage.fill(backgroundColor().rgba());

    initializeTileMap();

    emit onRenderMessage("Building boudary tree...");
    timer.start();
    buildBoundingTree();
    emit onRenderMessage(tr("Ok. Time: %0.").arg(timer.elapsed()));

    emit onRenderMessage("Tracing...");
    int renderingTime = 0;
    QRect tile;
    while (getNextTile(tile))
    {
        timer.start();
        renderRect(resultImage, tile);
        renderingTime += timer.elapsed();
        emit onTemporaryImageUpdated(resultImage);
        QThread::sleep(5);
    }
    emit onRenderMessage(tr("Ok. Time: %0.").arg(renderingTime));

    deleteTileMap();
    deleteBoundingTree();

    return resultImage;
}

void HTracer3::addPolygon(const QVector3D &v1, const QVector3D &v2, const QVector3D &v3, const QString &materialName)
{
    colliders_.append(new HPolygonCollider(v1, v2, v3, materials_[materialName]));
}

void HTracer3::addMaterial(const QString &name, const QColor &diffuseColor)
{
    materials_.insert(name, HMaterial(diffuseColor));
}

void HTracer3::addPointLight(const QVector3D &position)
{
    pointLights_.append(position);
}

void HTracer3::transformScene(const QMatrix4x4 &matrix)
{
    for (int i = 0; i < colliders_.length(); i++)
    {
        colliders_.at(i)->transform(matrix);
    }
    for (int i = 0; i < pointLights_.length(); i++)
    {
        pointLights_[i] = matrix * pointLights_[i];
    }
}

HFrustum HTracer3::cameraFrustum() const
{
    return cameraFrustum_;
}

void HTracer3::setCameraFrustum(const HFrustum &cameraFrustum)
{
    cameraFrustum_ = cameraFrustum;
}

QSize HTracer3::imageSize() const
{
    return imageSize_;
}

void HTracer3::setImageSize(const QSize &imageSize)
{
    imageSize_ = imageSize;
}

QSize HTracer3::tileSize() const
{
    return tileSize_;
}

void HTracer3::setTileSize(const QSize &tileSize)
{
    tileSize_ = tileSize;
}

QColor HTracer3::backgroundColor() const
{
    return backgroundColor_;
}

void HTracer3::setBackgroundColor(const QColor &backgroundColor)
{
    backgroundColor_ = backgroundColor;
}

void HTracer3::initializeTileMap()
{
    widthTiles_ = imageSize().width() / tileSize().width() +
            (imageSize().width() % tileSize().width() == 0 ? 0 : 1);

    heightTiles_ = imageSize().height() / tileSize().height() +
            (imageSize().height() % tileSize().height() == 0 ? 0 : 1);

    renderedTiles_ = 0;

    tileMap_ = new bool[widthTiles_ * heightTiles_];

    for (int i = 0; i < widthTiles_ * heightTiles_; i++)
        tileMap_[i] = false;
}

void HTracer3::deleteTileMap()
{
    delete[] tileMap_;
}

bool HTracer3::getNextTile(QRect &rect)
{
    QPoint midleTile(widthTiles_ / 2, heightTiles_ / 2);
    QPoint closestTile;
    bool isImageFinished = true;

    for (int y = 0; y < heightTiles_; y++)
        for (int x = 0; x < widthTiles_; x++)
        {
            QPoint currentTile(x, y);
            bool isCurrentTileRendered = tileMap_[y * widthTiles_ + x];
            if (!isCurrentTileRendered)
            {
                if (isImageFinished)
                {
                    isImageFinished = false;
                    closestTile = currentTile;
                }
                else
                {
                    if (distance(midleTile, currentTile) < distance(midleTile, closestTile))
                    {
                        closestTile = currentTile;
                    }
                }
            }
        }

    if (isImageFinished)
        return false;

    tileMap_[closestTile.y() * widthTiles_ + closestTile.x()] = true;

    int x = closestTile.x() * tileSize_.width();
    int y = closestTile.y() * tileSize_.height();

    rect = QRect(x, y,
                 qMin(tileSize_.width(), imageSize_.width() - x),
                 qMin(tileSize_.height(), imageSize_.height() - y));
    return true;
}

void HTracer3::deleteColliders()
{
    for (int i = 0; i < colliders_.length(); i++)
        delete colliders_.at(i);

    colliders_.clear();
}

void HTracer3::buildBoundingTree()
{
    QVector<ICollider *> clones;

    for (int i = 0; i < colliders_.length(); i++)
    {
        HBoundingSphereCollider *hbsc = new HBoundingSphereCollider();
        hbsc->addCollider(colliders_.at(i)->clone());

        clones.append(hbsc);
    }

    while (clones.length() != 1)
    {
        ICollider *closestToFirst = clones.at(1);

        float dist = clones.at(0)->getBoundingSphere().center()
                .distanceToPoint(closestToFirst->getBoundingSphere().center());

        for (int i = 1; i < clones.length(); i++)
        {
            float currentDist = clones.at(0)->getBoundingSphere().center()
                    .distanceToPoint(clones.at(i)->getBoundingSphere().center());

            if (currentDist < dist)
            {
                closestToFirst = clones.at(i);
                dist = clones.at(0)->getBoundingSphere().center()
                        .distanceToPoint(closestToFirst->getBoundingSphere().center());
            }
        }

        HBoundingSphereCollider *hbsc = new HBoundingSphereCollider();
        hbsc->addCollider(clones.at(0));
        hbsc->addCollider(closestToFirst);

        clones.removeAt(0);
        clones.removeOne(closestToFirst);

        clones.append(hbsc);
    }

    boundingTreeHead_ = clones.at(0);
}

void HTracer3::deleteBoundingTree()
{
    delete boundingTreeHead_;
}

float HTracer3::lambertLightScheme(const HCollision &ci) const
{
    float maxLightness = 0;

    for (int i = 0; i < pointLights_.length(); i++)
    {
        float currentLightness = qMax((float)0, QVector3D::dotProduct(ci.normal().normalized(), (pointLights_.at(i) - ci.point()).normalized()));
        maxLightness = qMax(maxLightness, currentLightness);
    }

    return maxLightness;
}

float HTracer3::ambientOcclusionLightScheme(const HCollision &ci, int samples) const
{
    int intersectedRays = 0;

    for (int i = 0; i < samples; i++)
    {
        QVector3D direction(-1 + qrand() / (double)RAND_MAX * 2.0,
                         -1 + qrand() / (double)RAND_MAX * 2.0,
                         -1 + qrand() / (double)RAND_MAX * 2.0);

        if (QVector3D::dotProduct(direction, ci.normal()) < 0)
            direction = -direction;

        HCollision tmpCi;
        if (computeCollision(HRay(ci.point(), direction), tmpCi))
            intersectedRays++;
    }

    return 1 - (float)intersectedRays / samples;
}

float HTracer3::shadowLightScheme(const HCollision &ci) const
{
    for (int i = 0; i < pointLights_.length(); i++)
    {
        HCollision shadowRayCi;
        if (computeCollision(HRay(ci.point(), pointLights_[i] - ci.point()), shadowRayCi))
        {
            if ((ci.point() - shadowRayCi.point()).length() > (ci.point() - pointLights_[i]).length())
            {
                return 1;
            }
        }
        else
        {
            return 1;
        }
    }

    return 0;
}

void HTracer3::renderRect(QImage &image, const QRect &rect) const
{
    for (int y = rect.top(); y < rect.top() + rect.height(); y++)
        for(int x = rect.left(); x < rect.left() + rect.width(); x++)
        {
            renderPixel(image, QPoint(x, y));
        }
}

void HTracer3::renderPixel(QImage &image, const QPoint &pixel) const
{
    HRay ray = computeRayForPixel(pixel);
    HCollision ci;
    QColor resultColor = Qt::black;

    if (computeCollision(ray, ci))
    {
        float lightness;
        float lsl = qMin(lambertLightScheme(ci), shadowLightScheme(ci));
        float ao = ambientOcclusionLightScheme(ci, 25);
        lightness = ao * 0.6 + lsl * 0.4;
        resultColor = mixColors(ci.material().diffuseColor(), Qt::black, lightness, 1 - lightness);
    }

    image.setPixel(pixel, resultColor.rgba());
}

HRay HTracer3::computeRayForPixel(const QPoint &point) const
{
    return HRay(QVector3D(0, 0, 0),
                QVector3D(cameraFrustum_.left() + (cameraFrustum_.right() - cameraFrustum_.left())
                            / imageSize_.width() * point.x(),
                          cameraFrustum_.bottom() + (cameraFrustum_.top() - cameraFrustum_.bottom())
                            / imageSize_.height() * (imageSize_.height() - point.y() - 1),
                          -cameraFrustum_.nearPlane()));
}

bool HTracer3::computeCollision(const HRay &ray, HCollision &collisionInfo) const
{
    return boundingTreeHead_->detectCollision(ray, collisionInfo);
}

QColor HTracer3::mixColors(const QColor &c1, const QColor &c2, float k1, float k2)
{
    return QColor((c1.red() * k1 + c2.red() * k2)/(k1 + k2),
                  (c1.green() * k1 + c2.green() * k2)/(k1 + k2),
                  (c1.blue() * k1 + c2.blue() * k2)/(k1 + k2));
}

float HTracer3::distance(const QPoint &p1, const QPoint &p2)
{
    float x = p1.x() - p2.x();
    float y = p1.y() - p2.y();
    return sqrt(x * x + y * y);
}
