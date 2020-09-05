#include <windows.h>
#include "vectors.h"
#include "constants.h"
#include "support_functions.h"

namespace SupportFunctions
{

    void setColor(int background, int text)
    {
        HANDLE hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsoleHandle, (WORD)((background << 4) | text));
    }

    void setCursor(short x, short y)
    {
        if(x == y)
            setColor(Constants::color_white);
        else if(x % 2 == 0 && y % 2 == 0)
            setColor(Constants::color_white);
        else if(x % 2 != 0 && y % 2 != 0)
            setColor(Constants::color_white);
        else if(x % 2 == 0 || y % 2 == 0)
            setColor(Constants::color_green);


        if(y > 9)
            setColor(Constants::color_black, Constants::color_white);

        // 1 cell = 2 space
        x  = (x * 2) + 1;
        y += 3;

        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD){x, y});
    }

    Vector  getContrastVector(Vector vector)
    {
        switch (vector)
        {
        case Vector::NORTH: return Vector::SOUTH;
        case Vector::N_E:   return Vector::S_W;
        case Vector::EAST:  return Vector::WEST;
        case Vector::S_E:   return Vector::N_W;
        case Vector::SOUTH: return Vector::NORTH;
        case Vector::S_W:   return Vector::N_E;
        case Vector::WEST:  return Vector::EAST;
        case Vector::N_W:   return Vector::S_E;
        }
    }
}
