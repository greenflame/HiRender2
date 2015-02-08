#include "hskyshader.h"

HSkyShader::HSkyShader()
{

}

HSkyShader::HSkyShader(const QString &textureName)
{
    setTextureName(textureName);
}

HSkyShader::~HSkyShader()
{

}

QColor HSkyShader::process(const HCollision &collision, const HTracer3 &tracer) const
{
    QImage &texture = *tracer.textures_[textureName_];
    QVector3D ratDirection = -collision.directionToEye();

    float yAngle = acosf(QVector3D::dotProduct(QVector3D(0, 1, 0), ratDirection));
    QVector3D xzProjection = QVector3D(ratDirection.x(), 0, ratDirection.z()).normalized();
    float zAngle = acosf(QVector3D::dotProduct(QVector3D(0, 0, 1), xzProjection));
    float xAngle = acosf(QVector3D::dotProduct(QVector3D(1, 0, 0), xzProjection));

    if (xAngle < M_PI / 2)
        zAngle = 2 * M_PI - zAngle;

    QPoint textureCoordinates;
    textureCoordinates.setX((texture.width() - 1) * (zAngle / (2 * M_PI)));
    textureCoordinates.setY((texture.height() - 1) * (yAngle / M_PI));

    return texture.pixel(textureCoordinates);
}

QString HSkyShader::textureName() const
{
    return textureName_;
}

void HSkyShader::setTextureName(const QString &textureName)
{
    textureName_ = textureName;
}


