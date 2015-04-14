#include "smaterial.h"

SMaterial::SMaterial()
{

}

SMaterial::SMaterial(const QColor &diffuseColor)
{
    setDiffuseColor(diffuseColor);
}

SMaterial::~SMaterial()
{

}

QColor SMaterial::diffuseColor() const
{
    return diffuseColor_;
}

void SMaterial::setDiffuseColor(const QColor &diffuseColor)
{
    diffuseColor_ = diffuseColor;
}


