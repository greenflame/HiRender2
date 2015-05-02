#ifndef HSKYSHADER_H
#define HSKYSHADER_H

#include "ishader.h"
#include "htracer3.h"

class HSkyShader : public IShader
{
public:
    HSkyShader();
    HSkyShader(const QString &textureName);
    ~HSkyShader();

    // IShader interface
    QColor process(const HCollision &collision, const HTracer3 &tracer, QStack<IShader *> &shaderStack) const;

    QString textureName() const;
    void setTextureName(const QString &textureName);

private:
    QString textureName_;
};

#endif // HSKYSHADER_H
