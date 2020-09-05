#include "participant.h"
#include "constants.h"
#include "support_functions.h"
#include <iostream>
#include "pointxy.h"

//player move
void Participant::makeMove()
{
    SupportFunctions::setCursor(Constants::input_x, Constants::input_y);
    std::cout << "Enter X:";
    int x{ 0 };
    std::cin >> x;
    SupportFunctions::setCursor(Constants::input_x + 5, Constants::input_y);
    std::cout << "Enter Y:";
    int y{ 0 };
    std::cin >> y;
    SupportFunctions::setCursor(x, y);
    std::cout << m_sign;
    m_points.push_back(PointXY(x,y));
}

void Participant::makeMove(const PointXY &point)
{
    SupportFunctions::setCursor(point.m_x, point.m_y);
    std::cout << m_sign;
    m_points.push_back(point);
}

bool Participant::isNearPoint(const PointXY &point) const
{
    for(const auto &element : m_points)
        if(element == point)
            return true;
    return false;
}

bool Participant::isContainPoint(const PointXY &point) const
{
    for(const auto &element : m_points)
        if(element == point)
            return true;
    return false;
}
