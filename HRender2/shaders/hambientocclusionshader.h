/*
 * AO shader
 */

#ifndef HAMBIENTOCCLUSIONSHADER_H
#define HAMBIENTOCCLUSIONSHADER_H

#include "ishader.h"
#include "htracer3.h"

class HAmbientOcclusionShader : public IShader
{
public:
    HAmbientOcclusionShader();
    HAmbientOcclusionShader(int iterations, QColor diffuseColor);
    ~HAmbientOcclusionShader();

    // IShader interface
    QColor process(const HCollision &collision, const HTracer3 &tracer, QStack<IShader *> &shaderStack) const;

    int iterations() const;
    void setIterations(int iterations);

    QColor diffuseColor() const;
    void setDiffuseColor(const QColor &diffuseColor);

private:
    int iterations_;
    QColor diffuseColor_;

};

#endif // HAMBIENTOCCLUSIONSHADER_H
