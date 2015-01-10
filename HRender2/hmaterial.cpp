#include "hmaterial.h"


QColor HMaterial::diffuseColor() const
{
    return diffuseColor_;
}

void HMaterial::setDiffuseColor(const QColor &diffuseColor)
{
    diffuseColor_ = diffuseColor;
}
