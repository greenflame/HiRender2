#include "hrefractionshader.h"

HRefractionShader::HRefractionShader()
{

}

HRefractionShader::HRefractionShader(float ior)
{
    setIor(ior);
}

HRefractionShader::~HRefractionShader()
{

}

QColor HRefractionShader::process(const HCollision &collision, const HTracer3 &tracer, QStack<IShader *> &shaderStack) const
{
    if (shaderStack.length() > tracer.rayLifeTime())
        return Qt::red;

    return Qt::blue;
}

float HRefractionShader::ior() const
{
    return ior_;
}

void HRefractionShader::setIor(float ior)
{
    ior_ = ior;
}


