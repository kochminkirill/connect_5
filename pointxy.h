#ifndef POINTXY_H
#define POINTXY_H
#include "vectors.h"
#include "participant.h"
#include <ostream>

class PointXY
{
public:
    explicit PointXY(int x = 0, int y = 0) : m_x{ x }, m_y{ y }{}

    PointXY getPointByVector(Vector) const;
    friend bool operator==(const PointXY&, const PointXY&);
    friend void Participant::makeMove(const PointXY&);
    friend bool operator!=(const PointXY&, const PointXY&);
    friend std::ostream& operator<<(std::ostream&, const PointXY&);

private:
    int m_x;
    int m_y;
};

#endif
