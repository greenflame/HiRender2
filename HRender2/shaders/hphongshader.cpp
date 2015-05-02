#include "hphongshader.h"

HPhongShader::HPhongShader()
{
    setDiffuseColor(Qt::gray);
}

HPhongShader::HPhongShader(const QColor &diffuseColor)
{
    setDiffuseColor(diffuseColor);
}

QColor HPhongShader::process(const HCollision &collision, const HTracer3 &tracer, QStack<IShader *> &shaderStack) const
{
    float lightness = qMin(lambertLightScheme(collision, tracer), shadowLightScheme(collision, tracer));
    QColor resultColor = HTracer3::mixColors(diffuseColor(), Qt::black, lightness, 1 - lightness);
    return resultColor;
}

QColor HPhongShader::diffuseColor() const
{
    return diffuseColor_;
}

void HPhongShader::setDiffuseColor(const QColor &diffuseColor)
{
    diffuseColor_ = diffuseColor;
}

float HPhongShader::lambertLightScheme(const HCollision &ci, const HTracer3 &tracer) const
{
    float maxLightness = 0;

    for (int i = 0; i < tracer.pointLights_.length(); i++)
    {
        float currentLightness = qMax((float)0, QVector3D::dotProduct(ci.normal(), (tracer.pointLights_.at(i) - ci.point()).normalized()));
        maxLightness = qMax(maxLightness, currentLightness);
    }

    return maxLightness;
}

float HPhongShader::shadowLightScheme(const HCollision &ci, const HTracer3 &tracer) const
{
    for (int i = 0; i < tracer.pointLights_.length(); i++)
    {
        QVector3D shadowRayCp;
        ICollider *tmpCollider;
        if (tracer.boundingTreeHead_->detectCollision(HRay(ci.point(), tracer.pointLights_[i] - ci.point()), shadowRayCp, &tmpCollider))
        {
            if ((ci.point() - shadowRayCp).length() > (ci.point() - tracer.pointLights_[i]).length())
            {
                return 1;
            }
        }
        else
        {
            return 1;
        }
    }

    return 0;
}
