#ifndef HMATERIAL_H
#define HMATERIAL_H

#include <QColor>

class HMaterial
{
public:
    HMaterial();
    HMaterial(const QColor &diffuseColor);
    HMaterial(const QColor &ambientColor, const QColor &diffuseColor, const QColor &specularColor,
              float specularFactor, float transparencyFacor);
    ~HMaterial();

    QColor ambientColor() const;
    void setAmbientColor(const QColor &ambientColor);

    QColor diffuseColor() const;
    void setDiffuseColor(const QColor &diffuseColor);

    QColor specularColor() const;
    void setSpecularColor(const QColor &specularColor);

    float specularFactor() const;
    void setSpecularFactor(float specularFactor);

    float transparencyFacor() const;
    void setTransparencyFacor(float transparencyFacor);

private:
    QColor ambientColor_;
    QColor diffuseColor_;

    QColor specularColor_;
    float specularFactor_;

    float transparencyFacor_;
};

#endif // HMATERIAL_H
