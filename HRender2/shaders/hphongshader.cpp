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
    float maxLightness = 0;

    for (int i = 0; i < tracer.pointLights_.length(); i++)
    {
        QVector3D currentLamp = tracer.pointLights_.at(i);

        HRay shadowRay = HRay(collision.point(), currentLamp - collision.point());
        QVector3D shadowRayCp;
        bool isLampVisible = false;

        if (tracer.boundingTreeHead_->detectCollision(shadowRay, shadowRayCp))
        {
            if ((collision.point() - shadowRayCp).length() > (collision.point() - currentLamp).length())
            {
                isLampVisible = true;
            }
        }
        else
        {
            isLampVisible = true;
        }

        if (isLampVisible)
        {
            maxLightness = qMax(maxLightness, QVector3D::dotProduct(collision.normal(), (currentLamp - collision.point()).normalized()));
        }
    }

    QColor resultColor = HTracer3::mixColors(diffuseColor_, Qt::black, maxLightness, 1 - maxLightness);
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
