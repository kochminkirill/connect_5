#ifndef SUPPORT_FUNCTIONS_H
#define SUPPORT_FUNCTIONS_H

#include "vectors.h"
#include "constants.h"

namespace SupportFunctions
{
    void setColor(int b, int t = Constants::color_black);
    void setCursor(short x, short y);
    Vector getContrastVector(Vector);
    int getRandomNumber(int min, int max);
}

#endif
