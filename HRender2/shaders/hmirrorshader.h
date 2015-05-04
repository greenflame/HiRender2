#ifndef HMIRRORSHADER_H
#define HMIRRORSHADER_H

#include "ishader.h"
#include "htracer3.h"

class HMirrorShader : public IShader
{
public:
    HMirrorShader();
    HMirrorShader(float spreadAngle, int iterations);
    ~HMirrorShader();

    // IShader interface
    QColor process(const HCollision &collision, const HTracer3 &tracer, QStack<IShader *> &shaderStack) const;

    float spreadAngle() const;
    void setSpreadAngle(float spreadAngle);

    int iterations() const;
    void setIterations(int iterations);

private:
    float spreadAngle_;
    int iterations_;

    static QVector3D reflectRay(const QVector3D &ray, const QVector3D &normal);
};

#endif // HMIRRORSHADER_H
