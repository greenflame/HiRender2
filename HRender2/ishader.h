#ifndef ISHADER_H
#define ISHADER_H

#include <QColor>

#include <hcollision.h>

class IShader
{
public:
    virtual ~IShader() = 0;

    virtual QColor process(const HCollision &collision) const = 0;
};

#endif // ISHADER_H
