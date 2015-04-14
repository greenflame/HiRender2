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

#include "ishader.h"
#include "hphongshader.h"
#include "hskyshader.h"
#include "hmirrorshader.h"

#include "icollider.h"
#include "hfrustum.h"
#include "hboundingspherecollider.h"
#include "hpolygoncollider.h"
#include "hspherecollider.h"
#include "icollider.h"

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

    void addSphere(const QVector3D &center, float radius, const QString &shaderName = "default");

    // Shaders
    void addPhongShader(const QString &name, const QColor &diffuseColor);

    // Lights
    void addPointLight(const QVector3D &position);

    //Textures
    void addTexture(const QString &name, const QImage &image);  ///not used?

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

signals:
    void onTemporaryImageUpdated(QImage image);
    void onRenderMessage(QString message);

private:
    friend class HPhongShader;
    friend class HSkyShader;
    friend class HMirrorShader;

    // Camera settings
    HFrustum cameraFrustum_;
    QMatrix4x4 cameraMatrix_;

    // Image settings
    QSize imageSize_;
    QSize tileSize_;
    QColor backgroundColor_;

    // Tile controller
    bool *tileMap_;
    int widthTiles_;
    int heightTiles_;
    int renderedTiles_;
    void initializeTileMap();
    void deleteTileMap();
    bool getNextTile(QRect &rect);

    // Colliders list
    QVector<ICollider *> colliders_;
    void deleteColliders();

    // Colliders bounding tree controller
    ICollider *boundingTreeHead_;
    void buildBoundingTree();
    void deleteBoundingTree();

    // Materials
    QMap<QString, IShader*> shaders_;
    void deleteShaders();

    // Lamps
    QVector<QVector3D> pointLights_;

    // Textures
    QMap<QString, QImage*> textures_;
    void deleteTextures();

    // Light schemes
    float ambientOcclusionLightScheme(const HCollision &ci, int samples) const; ///???????whf???

    // STH... render
    void renderRect(QImage &image, const QRect &rect) const;
    void renderPixel(QImage &image, const QPoint &pixel) const;
    QColor traceRay(const HRay &ray) const;

    HRay computeRayForPixel(const QPoint &point) const;

    // STH.. static
    static QColor mixColors(const QColor &c1, const QColor &c2, float k1, float k2);
    static float distance(const QPoint &p1, const QPoint &p2);


};

#endif // HTRACER3_H
