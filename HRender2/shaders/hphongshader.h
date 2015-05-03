#ifndef HPHONGSHADER_H
#define HPHONGSHADER_H

#include "ishader.h"
#include "htracer3.h"

class HPhongShader : public IShader
{
public:
    HPhongShader();
    HPhongShader(const QColor &diffuseColor);

    // IShader interface
    QColor process(const HCollision &collision, const HTracer3 &tracer, QStack<IShader *> &shaderStack) const;

    QColor diffuseColor() const;
    void setDiffuseColor(const QColor &diffuseColor);

private:
    QColor diffuseColor_;
};

#endif // HFHONGSHADER_H
