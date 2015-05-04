#include "htracer3.h"

HTracer3::HTracer3(QObject *parent) : QObject(parent)
{
    setCameraFrustum(HFrustum(-0.9, 0.9, -0.5, 0.5, 1, 1000));
    setImageSize(QSize(1280, 720));
    setTileSize(QSize(128, 128));
    setBackgroundColor(Qt::black);
    setRayLifeTime(8);

    addPhongShader("default", Qt::gray);
}

HTracer3::~HTracer3()
{
    deleteColliders();
    deleteShaders();
}

QImage HTracer3::render()
{
    QTime timer;

    QImage resultImage(imageSize(), QImage::Format_ARGB32);
    resultImage.fill(backgroundColor().rgba());

    if (colliders_.length() == 0)
        return resultImage;

    HTileController tileController(imageSize_, tileSize_);

    if (bvh.isEmpty())
    {
        emit onRenderMessage("Building boudary tree...");
        timer.start();
        bvh.build(colliders_);
        emit onRenderMessage(tr("Ok. Time: %0.").arg(timer.elapsed()));
    }
    else
    {
        emit onRenderMessage("Boundary tree already builded.");
    }

    emit onRenderMessage("Tracing...");
    int renderingTime = 0;
    QRect tile;
    while (tileController.getNextTile(tile))
    {
        timer.start();
        renderRect(resultImage, tile);
        renderingTime += timer.elapsed();
        emit onTemporaryImageUpdated(resultImage);
    }
    emit onRenderMessage(tr("Ok. Time: %0.").arg(renderingTime));

    return resultImage;
}

void HTracer3::addPolygon(const QVector3D &v1, const QVector3D &v2, const QVector3D &v3, const QString &shaderName)
{
    QString resultMaterialName = shaderName;
    if (!shaders_.contains(shaderName))
        resultMaterialName = "default";

    colliders_.append(new HPolygonCollider(v1, v2, v3, shaders_[resultMaterialName]));
}

void HTracer3::addPolygon(const QVector3D &v1, const QVector3D &v2, const QVector3D &v3,
                          const QVector3D &n1, const QVector3D &n2, const QVector3D &n3, const QString &shaderName)
{
    QString resultShaderName = shaders_.contains(shaderName) ? shaderName : "default";

    HPolygonCollider *collider = new HPolygonCollider(v1, v2, v3, shaders_[resultShaderName]);
    collider->setN1(n1);
    collider->setN2(n2);
    collider->setN3(n3);
    collider->setUseNormals(true);

    colliders_.append(collider);
}

void HTracer3::addPhongShader(const QString &name, const QColor &diffuseColor)
{
    shaders_.insert(name, new HPhongShader(diffuseColor));
}

void HTracer3::addMirrorShader(const QString &name, float spreadAngle, int iterations)
{
    shaders_.insert(name, new HMirrorShader(spreadAngle, iterations));
}

void HTracer3::addRefractionShader(const QString &name, float ior)
{
    shaders_.insert(name, new HRefractionShader(ior));
}

void HTracer3::addAmbientOcclusionShader(const QString &name, int iterations)
{
    shaders_.insert(name, new HAmbientOcclusionShader(iterations));
}

void HTracer3::addPointLight(const QVector3D &position)
{
    pointLights_.append(position);
}

void HTracer3::addTexture(const QString &name, const QImage &image)
{
    textures_.insert(name, new QImage(image));
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

QMatrix4x4 HTracer3::cameraMatrix() const
{
    return cameraMatrix_;
}

void HTracer3::setCameraMatrix(const QMatrix4x4 &cameraMatrix)
{
    cameraMatrix_ = cameraMatrix;
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

int HTracer3::rayLifeTime() const
{
    return rayLifeTime_;
}

void HTracer3::setRayLifeTime(int rayLifeTime)
{
    rayLifeTime_ = rayLifeTime;
}

void HTracer3::deleteColliders()
{
    for (int i = 0; i < colliders_.length(); i++)
        delete colliders_.at(i);

    colliders_.clear();
}

void HTracer3::deleteShaders()
{
    QList<IShader *> pointers = shaders_.values();

    for (int i = 0; i < pointers.length(); i++)
        delete pointers.at(i);

    shaders_.clear();
}

void HTracer3::deleteTextures()
{
    QList<QImage*> pointers = textures_.values();

    for (int i = 0; i < pointers.length(); i++)
        delete pointers.at(i);

    textures_.clear();
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

    QStack<IShader *> shaderStack;

    QColor resultColor = traceRay(ray, shaderStack);
    image.setPixel(pixel, resultColor.rgba());
}

QColor HTracer3::traceRay(const HRay &ray, QStack<IShader *> shaderStack) const
{
    QColor resultColor;

    bool isCollisionExist = bvh.head()->processCollision(ray, *this, resultColor, shaderStack);

    if (!isCollisionExist)
    {
        if (textures_.contains("skyTexture"))
        {
            resultColor = HSkyShader("skyTexture").process(HCollision(QVector3D(0, 0, 0),
                                                                    QVector3D(0, 0, 0),
                                                                    -ray.direction()),
                                                                    *this,
                                                                    shaderStack);
        }
        else
        {
            resultColor = backgroundColor();
        }
    }

    return resultColor;
}

HRay HTracer3::computeRayForPixel(const QPoint &point) const
{
    return HRay(QVector3D(0, 0, 0),
                QVector3D(cameraFrustum_.left() + (cameraFrustum_.right() - cameraFrustum_.left())
                            / imageSize_.width() * point.x(),
                          cameraFrustum_.bottom() + (cameraFrustum_.top() - cameraFrustum_.bottom())
                            / imageSize_.height() * (imageSize_.height() - point.y() - 1),
                          -cameraFrustum_.nearPlane())).transformed(cameraMatrix_.inverted());
}

QColor HTracer3::mixColors(const QColor &c1, const QColor &c2, float k1, float k2)
{
    return QColor((c1.red() * k1 + c2.red() * k2)/(k1 + k2),
                  (c1.green() * k1 + c2.green() * k2)/(k1 + k2),
                  (c1.blue() * k1 + c2.blue() * k2)/(k1 + k2));
}
