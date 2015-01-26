#include "hmaterial.h"


HMaterial::HMaterial()
{
    setAmbientColor(Qt::white);
    setDiffuseColor(Qt::gray);
    setSpecularColor(Qt::white);
    setSpecularFactor(0);
    setTransparencyFacor(0);
}

HMaterial::HMaterial(const QColor &diffuseColor)
{
    setAmbientColor(Qt::white);
    setDiffuseColor(diffuseColor);
    setSpecularColor(Qt::white);
    setSpecularFactor(0);
    setTransparencyFacor(0);
}

HMaterial::HMaterial(const QColor &ambientColor, const QColor &diffuseColor, const QColor &specularColor,
                     float specularFactor, float transparencyFacor)
{
    setAmbientColor(ambientColor);
    setDiffuseColor(diffuseColor);
    setSpecularColor(specularColor);
    setSpecularFactor(specularFactor);
    setTransparencyFacor(transparencyFacor);
}

HMaterial::~HMaterial()
{

}

QColor HMaterial::ambientColor() const
{
    return ambientColor_;
}

void HMaterial::setAmbientColor(const QColor &ambientColor)
{
    ambientColor_ = ambientColor;
}

QColor HMaterial::diffuseColor() const
{
    return diffuseColor_;
}

void HMaterial::setDiffuseColor(const QColor &diffuseColor)
{
    diffuseColor_ = diffuseColor;
}

QColor HMaterial::specularColor() const
{
    return specularColor_;
}

void HMaterial::setSpecularColor(const QColor &specularColor)
{
    specularColor_ = specularColor;
}

float HMaterial::specularFactor() const
{
    return specularFactor_;
}

void HMaterial::setSpecularFactor(float specularFactor)
{
    specularFactor_ = specularFactor;
}

float HMaterial::transparencyFacor() const
{
    return transparencyFacor_;
}

void HMaterial::setTransparencyFacor(float transparencyFacor)
{
    transparencyFacor_ = transparencyFacor;
}
