#include "haccuracy.h"

bool HAccuracy::floatEqual(float a, float b)
{
    return abs(a - b) < EPSILON;
}

bool HAccuracy::floatLessOrEqual(float a, float b)
{
    return a < b || floatEqual(a, b);
}

bool HAccuracy::floatLess(float a, float b)
{
    return a < b && !floatEqual(a, b);
}

bool HAccuracy::floatGreaterOrEqual(float a, float b)
{
    return a > b || floatEqual(a, b);
}

bool HAccuracy::floatGreater(float a, float b)
{
    return a > b && !floatEqual(a, b);
}
