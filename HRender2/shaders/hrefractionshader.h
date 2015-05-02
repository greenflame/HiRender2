/*
 * Refraction shader
 * Created 23.04.2015 by Alexander
 */

#ifndef HREFRACTIONSHADER_H
#define HREFRACTIONSHADER_H

#include "ishader.h"
#include "htracer3.h"

class HRefractionShader : public IShader
{
public:
    HRefractionShader();
    HRefractionShader(float ior);
    ~HRefractionShader();

    // IShader interface
    QColor process(const HCollision &collision, const HTracer3 &tracer, QStack<IShader *> &shaderStack) const;

    float ior() const;
    void setIor(float ior);

private:
    float ior_;
};

#endif // HREFRACTIONSHADER_H
