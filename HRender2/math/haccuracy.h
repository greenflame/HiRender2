/*
 * Class provides comparation of floating point numbers.
 * Standart libraries.
 * !Unstable work.
 */

#ifndef HACCURACY_H
#define HACCURACY_H

#include <cmath>

#define EPSILON 0.00001

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
