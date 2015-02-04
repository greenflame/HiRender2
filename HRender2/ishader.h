#ifndef ISHADER_H
#define ISHADER_H

#include <QColor>

#include "hcollision.h"

class HTracer3;

class IShader
{
public:
    virtual ~IShader();

    virtual QColor process(const HCollision &collision, const HTracer3 &tracer) const = 0;
};

#endif // ISHADER_H
