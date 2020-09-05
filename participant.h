#ifndef PARTICIPANT_H
#define PARTICIPANT_H
#include <vector>

class PointXY;

class Participant
{
public:
    Participant(char sign) : m_sign{ sign } { m_points.reserve(15); }
    int getCountPoints() const { return m_points.size(); }
    //for Player
    void makeMove();
    //for Computer
    void makeMove(const PointXY&);
    const PointXY& operator[] (const int index) const { return m_points[index]; }
    bool isNearPoint(const PointXY&) const;
    bool isContainPoint(const PointXY&) const;

private:
    std::vector<PointXY> m_points;
    char m_sign;
};

#endif
