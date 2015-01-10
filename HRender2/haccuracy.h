#ifndef HACCURACY_H
#define HACCURACY_H

#include <stdlib.h>

#define EPSILON 0.000001

class HAccuracy
{
public:
    static bool floatEqual(float a, float b);
    static bool floatLessOrEqual(float a, float b);
    static bool floatLess(float a, float b);
    static bool floatGreaterOrEqual(float a, float b);
    static bool floatGreater(float a, float b);

};

#endif // HACCURACY_H
