//#ifndef HTRACER_H
//#define HTRACER_H

//#include <QObject>
//#include <QVector>
//#include <QMap>
//#include <QSize>
//#include <QColor>
//#include <QImage>
//#include <QString>
//#include <QMatrix4x4>

//#include <hmaterial.h>
//#include <icollider.h>
//#include <hfrustum.h>

//class HTracer : public QObject
//{
//    Q_OBJECT
//public:
//    explicit HTracer(QObject *parent = 0);
//    ~HTracer();

//    QImage render();
//    void loadObj();

//    // Accesors
//    HFrustum cameraFrustum() const;
//    void setCameraFrustum(const HFrustum &cameraFrustum);

//    QMatrix4x4 cameraMatrix() const;
//    void setCameraMatrix(const QMatrix4x4 &cameraMatrix);

//    QSize imageSize() const;
//    void setImageSize(const QSize &imageSize);

//    QSize tileSize() const;
//    void setTileSize(const QSize &tileSize);

//    QColor backgroundColor() const;
//    void setBackgroundColor(const QColor &backgroundColor);

//signals:
//    void onTemporaryImageUpdated(QImage image);
//    void onRenderMessage(QString message);

//private:
//    // Camera settings
//    HFrustum cameraFrustum_;
//    QMatrix4x4 cameraMatrix_;

//    // Image settings
//    QSize imageSize_;
//    QSize tileSize_;
//    QColor backgroundColor_;

//    // Tile controller
//    int *tileMap_;
//    void initializeTileMap();
//    void deleteTileMap();
//    bool getNextTile(QRect &rect);

//    // Colliders list
//    QVector<ICollider *> colliders_;
//    void deleteColliders();

//    // Colliders bounding tree controller
//    ICollider *boundingTree_;
//    void buildBoundingTree();
//    void deleteBoundingTree();

//    // Materials
//    QMap<QString, HMaterial> materials_;
//};

//#endif // HTRACER_H
