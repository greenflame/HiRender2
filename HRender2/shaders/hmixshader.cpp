#include "hmixshader.h"

HMixShader::HMixShader()
{
    setShader1(0);
    setShader2(0);

    setK1(0.5);
    setK1(0.5);
}

HMixShader::HMixShader(IShader *shader1, IShader *shader2, float k1, float k2)
{
    setShader1(shader1);
    setShader2(shader2);

    setK1(k1);
    setK2(k2);
}

HMixShader::~HMixShader()
{

}

QColor HMixShader::process(const HCollision &collision, const HTracer3 &tracer, QStack<IShader *> &shaderStack) const
{
    if (shader1_ == 0 || shader2_ == 0)
    {
        return tracer.backgroundColor();
    }

    QColor color1 = shader1_->process(collision, tracer, shaderStack);
    QColor color2 = shader2_->process(collision, tracer, shaderStack);

    return HTracer3::mixColors(color1, color2, k1_, k2_);
}

IShader *HMixShader::shader1() const
{
    return shader1_;
}

void HMixShader::setShader1(IShader *shader1)
{
    shader1_ = shader1;
}

IShader *HMixShader::shader2() const
{
    return shader2_;
}

void HMixShader::setShader2(IShader *shader2)
{
    shader2_ = shader2;
}

float HMixShader::k1() const
{
    return k1_;
}

void HMixShader::setK1(float k1)
{
    k1_ = k1;
}
float HMixShader::k2() const
{
    return k2_;
}

void HMixShader::setK2(float k2)
{
    k2_ = k2;
}





