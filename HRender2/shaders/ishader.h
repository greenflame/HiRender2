#ifndef ISHADER_H
#define ISHADER_H

#include <QColor>

#include "hcollision.h"

class HTracer3;

/*
 * Shader interface.
 */

class IShader
{
public:
    virtual ~IShader();

    /*
     *  Input:
     *  -collision [point, normal, to eye direction]
     *  -tracer [for additional ray emiting]
     *
     *  Output:
     *  -color [result color of the collision]
     */
    virtual QColor process(const HCollision &collision, const HTracer3 &tracer) const = 0;
};

#endif // ISHADER_H
