//#include "htracer.h"

//HTracer::HTracer(QObject *parent) : QObject(parent)
//{
//    setCameraFrustum(HFrustum(-0.9, 0.9, -0.5, 0.5, 1, 1000));
//    setImageSize(QSize(1280, 720));
//    setTileSize(QSize(128, 128));
//    setBackgroundColor(Qt::black);

//    boundingTree_ = 0;
//}

//HTracer::~HTracer()
//{
//    deleteColliders();
//}

//QImage HTracer::render()
//{
//    return QImage();
//}

//void HTracer::loadObj()
//{

//}

//HFrustum HTracer::cameraFrustum() const
//{
//    return cameraFrustum_;
//}

//void HTracer::setCameraFrustum(const HFrustum &cameraFrustum)
//{
//    cameraFrustum_ = cameraFrustum;
//}

//QMatrix4x4 HTracer::cameraMatrix() const
//{
//    return cameraMatrix_;
//}

//void HTracer::setCameraMatrix(const QMatrix4x4 &cameraMatrix)
//{
//    cameraMatrix_ = cameraMatrix;
//}

//QSize HTracer::imageSize() const
//{
//    return imageSize_;
//}

//void HTracer::setImageSize(const QSize &imageSize)
//{
//    imageSize_ = imageSize;
//}

//QSize HTracer::tileSize() const
//{
//    return tileSize_;
//}

//void HTracer::setTileSize(const QSize &tileSize)
//{
//    tileSize_ = tileSize;
//}

//QColor HTracer::backgroundColor() const
//{
//    return backgroundColor_;
//}

//void HTracer::setBackgroundColor(const QColor &backgroundColor)
//{
//    backgroundColor_ = backgroundColor;
//}

//void HTracer::initializeTileMap()
//{

//}

//void HTracer::deleteTileMap()
//{

//}

//bool HTracer::getNextTile(QRect &rect)
//{
//    return true;
//}

//void HTracer::deleteColliders()
//{

//}

//void HTracer::buildBoundingTree()
//{

//}

//void HTracer::deleteBoundingTree()
//{

//}
