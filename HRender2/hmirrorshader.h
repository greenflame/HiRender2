#ifndef HMIRRORSHADER_H
#define HMIRRORSHADER_H

#include "ishader.h"
#include "hlibrary.h"
#include "htracer3.h"

class HMirrorShader : public IShader
{
public:
    HMirrorShader();
    HMirrorShader(float spreadAngle, int iterations);
    ~HMirrorShader();

    // IShader interface
    QColor process(const HCollision &collision, const HTracer3 &tracer) const;

    float spreadAngle() const;
    void setSpreadAngle(float spreadAngle);

    int iterations() const;
    void setIterations(int iterations);

private:
    float spreadAngle_;
    int iterations_;
};

#endif // HMIRRORSHADER_H
