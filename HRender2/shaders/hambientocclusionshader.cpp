#include "hambientocclusionshader.h"

HAmbientOcclusionShader::HAmbientOcclusionShader()
{

}

HAmbientOcclusionShader::HAmbientOcclusionShader(int iterations)
{
    setIterations(iterations);
}

HAmbientOcclusionShader::~HAmbientOcclusionShader()
{

}

QColor HAmbientOcclusionShader::process(const HCollision &collision, const HTracer3 &tracer, QStack<IShader *> &shaderStack) const
{
    int intersectedRays = 0;

    for (int i = 0; i < iterations_; i++)
    {
        QVector3D randomDirection(-1 + qrand() / (double)RAND_MAX * 2.0,
                         -1 + qrand() / (double)RAND_MAX * 2.0,
                         -1 + qrand() / (double)RAND_MAX * 2.0);

        if (QVector3D::dotProduct(randomDirection, collision.normal()) < 0)
            randomDirection = -randomDirection;

        HRay randomRay(collision.point(), randomDirection);
        if (tracer.boundingTreeHead_->detectCollision(randomRay))
            intersectedRays++;
    }

    float k = 1 - (float)intersectedRays / iterations_;
    return QColor(255 * k, 255 * k, 255 * k);
}

int HAmbientOcclusionShader::iterations() const
{
    return iterations_;
}

void HAmbientOcclusionShader::setIterations(int iterations)
{
    iterations_ = iterations;
}
