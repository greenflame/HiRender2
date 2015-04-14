#ifndef SMATERIAL_H
#define SMATERIAL_H

#include <QColor>

class SMaterial
{
public:
    SMaterial();
    SMaterial(const QColor &diffuseColor);
    ~SMaterial();

    QColor diffuseColor() const;
    void setDiffuseColor(const QColor &diffuseColor);

private:
    QColor diffuseColor_;
};

#endif // SMATERIAL_H
