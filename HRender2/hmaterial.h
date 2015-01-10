#ifndef HMATERIAL_H
#define HMATERIAL_H

#include <QColor>

class HMaterial
{
public:
    HMaterial() {}
    HMaterial(QColor diffuseColor) : diffuseColor_(diffuseColor) {}

    QColor diffuseColor() const;
    void setDiffuseColor(const QColor &diffuseColor);

private:
    QColor diffuseColor_;

};

#endif // HMATERIAL_H
