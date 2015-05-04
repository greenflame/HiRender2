#ifndef HMIXSHADER_H
#define HMIXSHADER_H

#include "ishader.h"
#include "htracer3.h"

class HMixShader : public IShader
{
public:
    HMixShader();
    HMixShader(IShader *shader1, IShader *shader2, float k1, float k2);
    ~HMixShader();

    // IShader interface
    QColor process(const HCollision &collision, const HTracer3 &tracer, QStack<IShader *> &shaderStack) const;

    IShader *shader1() const;
    void setShader1(IShader *shader1);

    IShader *shader2() const;
    void setShader2(IShader *shader2);

    float k1() const;
    void setK1(float k1);

    float k2() const;
    void setK2(float k2);

private:
    IShader *shader1_;
    IShader *shader2_;

    float k1_;
    float k2_;
};

#endif // HMIXSHADER_H
