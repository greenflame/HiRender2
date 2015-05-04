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

// No comments. Test.
QColor HRefractionShader::process(const HCollision &collision, const HTracer3 &tracer, QStack<IShader *> &shaderStack) const
{
    if (shaderStack.length() > tracer.rayLifeTime())
        return Qt::red;

    float eta = 0;
    if (!shaderStack.isEmpty() && shaderStack.top() == const_cast<HRefractionShader *>(this))
    {
        eta = ior_;
    }
    else
    {
        eta = 1 / ior_;
    }

    HRay refractedRay(collision.point(), refract(-collision.directionToEye(), collision.normal(), eta));

    shaderStack.push(const_cast<HRefractionShader *>(this));
    QColor resultColor = tracer.traceRay(refractedRay, shaderStack);
    shaderStack.pop();

    return resultColor;
}

float HRefractionShader::ior() const
{
    return ior_;
}

void HRefractionShader::setIor(float ior)
{
    ior_ = ior;
}

// http://asawicki.info/news_1301_reflect_and_refract_functions.html
QVector3D HRefractionShader::refract(const QVector3D &incidentVec, const QVector3D &normal, float eta) const
{
  float N_dot_I = QVector3D::dotProduct(normal, incidentVec);
  float k = 1.f - eta * eta * (1.f - N_dot_I * N_dot_I);
  if (k < 0.f)
    return QVector3D(0.f, 0.f, 0.f);
  else
    return eta * incidentVec - (eta * N_dot_I + sqrtf(k)) * normal;
}
