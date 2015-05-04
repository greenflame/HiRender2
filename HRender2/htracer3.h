#ifndef HTRACER3_H
#define HTRACER3_H

#include <QObject>
#include <QVector>
#include <QMap>
#include <QSize>
#include <QColor>
#include <QImage>
#include <QString>
#include <QMatrix4x4>
#include <QFile>
#include <QTime>
#include <QString>
#include <QThread>

#include "shaders/hshaders.h"
#include "colliders/hcolliders.h"

#include "htilecontroller.h"
#include "hbvh.h"

#include "geometry/hfrustum.h"

class HTracer3 : public QObject
{
    Q_OBJECT
public:
    explicit HTracer3(QObject *parent = 0);
    ~HTracer3();

    QImage render();

    // Colliders
    void addPolygon(const QVector3D &v1, const QVector3D &v2, const QVector3D &v3, const QString &shaderName = "default");

    void addPolygon(const QVector3D &v1, const QVector3D &v2, const QVector3D &v3,
                    const QVector3D &n1, const QVector3D &n2, const QVector3D &n3, const QString &shaderName = "default");

    // Shaders
    void addMixShader(const QString &name, const QString &shader1, const QString &shader2, float k1, float k2);

    void addPhongShader(const QString &name, const QColor &diffuseColor);
    void addMirrorShader(const QString &name, float spreadAngle, int iterations);
    void addRefractionShader(const QString &name, float ior);
    void addAmbientOcclusionShader(const QString &name, int iterations, QColor diffuseColor);

    // Lights
    void addPointLight(const QVector3D &position);

    //Textures
    void addTexture(const QString &name, const QImage &image);

    // Scene
    void transformScene(const QMatrix4x4 &matrix);

    // Accesors
    HFrustum cameraFrustum() const;
    void setCameraFrustum(const HFrustum &cameraFrustum);

    QMatrix4x4 cameraMatrix() const;
    void setCameraMatrix(const QMatrix4x4 &cameraMatrix);

    QSize imageSize() const;
    void setImageSize(const QSize &imageSize);

    QSize tileSize() const;
    void setTileSize(const QSize &tileSize);

    QColor backgroundColor() const;
    void setBackgroundColor(const QColor &backgroundColor);

    int rayLifeTime() const;
    void setRayLifeTime(int rayLifeTime);

signals:
    void onTemporaryImageUpdated(QImage image);
    void onRenderMessage(QString message);

private:
    friend class HSkyShader;

    friend class HMixShader;

    friend class HPhongShader;
    friend class HMirrorShader;
    friend class HAmbientOcclusionShader;
    friend class HRefractionShader;

    // Camera settings
    HFrustum cameraFrustum_;
    QMatrix4x4 cameraMatrix_;

    // Image settings
    QSize imageSize_;
    QSize tileSize_;
    QColor backgroundColor_;

    // Render settings
    int rayLifeTime_;

    // Colliders list
    QVector<ICollider *> colliders_;
    void deleteColliders();
    HBVH bvh;

    // Materials
    QMap<QString, IShader*> shaders_;
    void deleteShaders();

    // Lamps
    QVector<QVector3D> pointLights_;

    // Textures
    QMap<QString, QImage*> textures_;
    void deleteTextures();

    // Render mechanics
    void renderRect(QImage &image, const QRect &rect) const;
    void renderPixel(QImage &image, const QPoint &pixel) const;
    HRay computeRayForPixel(const QPoint &point) const;
    QColor traceRay(const HRay &ray, QStack<IShader *> shaderStack) const;

    // STH.. static
    static QColor mixColors(const QColor &c1, const QColor &c2, float k1, float k2);

};

#endif // HTRACER3_H
