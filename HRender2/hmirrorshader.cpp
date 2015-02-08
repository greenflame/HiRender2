#include "hmirrorshader.h"

HMirrorShader::HMirrorShader()
{

}

HMirrorShader::HMirrorShader(float spreadAngle, int iterations)
{
    setSpreadAngle(spreadAngle);
    setIterations(iterations);
}

HMirrorShader::~HMirrorShader()
{

}

QColor HMirrorShader::process(const HCollision &collision, const HTracer3 &tracer) const
{
    QVector3D reflectedDirection = HLibrary::reflectRay(-collision.directionToEye(), collision.normal());
    int r = 0, g = 0, b = 0;

    for (int i = 0; i < iterations_; i++)
    {
        QVector3D randomDirection(-1 + qrand() / (double)RAND_MAX * 2.0,
                               -1 + qrand() / (double)RAND_MAX * 2.0,
                               -1 + qrand() / (double)RAND_MAX * 2.0);

        QMatrix4x4 matrix;
        matrix.rotate(spreadAngle_, randomDirection);
        HRay currentRay(collision.point(), matrix * reflectedDirection);

        QColor currentColor = tracer.traceRay(currentRay);

        r += currentColor.red();
        g += currentColor.green();
        b += currentColor.blue();
    }

    QColor resultColor(r / iterations_, g / iterations_, b / iterations_);
    return resultColor;
}

float HMirrorShader::spreadAngle() const
{
    return spreadAngle_;
}

void HMirrorShader::setSpreadAngle(float spreadAngle)
{
    spreadAngle_ = spreadAngle;
}

int HMirrorShader::iterations() const
{
    return iterations_;
}

void HMirrorShader::setIterations(int iterations)
{
    iterations_ = iterations;
}



