#include "pointxy.h"

PointXY PointXY::getPointByVector(Vector vector) const
{
    PointXY point(m_x, m_y);
    switch (vector)
    {
        case Vector::NORTH: --point.m_y; break;

        case Vector::N_E:   ++point.m_x;
                            --point.m_y; break;

        case Vector::EAST:  ++point.m_x; break;

        case Vector::S_E:   ++point.m_x;
                            ++point.m_y; break;

        case Vector::SOUTH: ++point.m_y; break;

        case Vector::S_W:   --point.m_x;
                            ++point.m_y; break;

        case Vector::WEST:  --point.m_x; break;

        case Vector::N_W:  --point.m_x;
                           --point.m_y; break;
    }

    if(point.m_x  <= 0 || point.m_y <= 0 || point.m_x >= 10 || point.m_y >= 10)
        return PointXY(0,0);

    return point;
}

bool operator==(const PointXY &p_1, const PointXY &p_2)
{
    return (p_1.m_x == p_2.m_x && p_1.m_y == p_2.m_y);
}

bool operator!=(const PointXY &p_1, const PointXY &p_2)
{
    return !(p_1 == p_2);
}

std::ostream& operator<<(std::ostream &out, const PointXY &point)
{
   out << "Point(" << point.m_x << ", " << point.m_y << ")\n";
   return out;
}
