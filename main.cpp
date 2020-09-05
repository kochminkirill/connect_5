#include "participant.h"
#include "support_functions.h"
#include "pointxy.h"

#include <iostream>

void drawGameField()
{
    const char horizontal_line   { static_cast<char>(196) };
    const char vertical_line     { static_cast<char>(179) };
    const char top_left_angle    { static_cast<char>(218) };
    const char top_right_angle   { static_cast<char>(191) };
    const char bottom_left_angle { static_cast<char>(192) };
    const char bottom_right_angle{ static_cast<char>(217) };

    std::cout << "\t\t\t\tConnect 5\n\n";

    //draw top line
    std::cout << "  ";
    SupportFunctions::setColor(Constants::color_black, Constants::color_white);
    for(int i{ 0 }; i < Constants::field_width; ++i)
        std::cout << i + 1 << " ";
    std::cout << '\n';

    std::cout << " " << top_left_angle;
    for(int i{ 0 }; i <Constants::field_width; ++i)
        std::cout << horizontal_line << horizontal_line;
    std::cout << top_right_angle << '\n';


    //draw body
    bool color_flag{ true };
    for(int row{ 0 }; row < Constants::field_height; ++row)
    {
        SupportFunctions::setColor(Constants::color_black, Constants::color_white);
        std::cout << row + 1 << vertical_line;
        for(int col{ 0 }; col < Constants::field_width; ++ col)
        {
            if(color_flag)
            {
                SupportFunctions::setColor(Constants::color_white);
                color_flag = false;
            }
            else
            {
                SupportFunctions::setColor(Constants::color_green);
                color_flag = true;
            }
            std::cout << "  ";
        }
        SupportFunctions::setColor(Constants::color_black, Constants::color_white);
        std::cout << vertical_line << '\n';
    }

    //draw bottom
    std::cout << " " << bottom_left_angle;
    for(int i{ 0 }; i <Constants::field_width; ++i)
        std::cout << horizontal_line << horizontal_line;
    std::cout << bottom_right_angle << '\n';
}

void makeSpace() { SupportFunctions::setCursor(0, Constants::input_y + 4); }


int calculatePoints(const PointXY &start_point, const Participant &participant, Vector vector, int &countP_v, int &countP_cv)
{
    int total_point{ 1 };
    PointXY point(start_point.getPointByVector(vector));

    while(participant.isNearPoint(point))
    {
        point = point.getPointByVector(vector);
        ++countP_v;
        ++total_point;
    }

    Vector contrast_vector(SupportFunctions::getContrastVector(vector));

    point = start_point.getPointByVector(contrast_vector);

    while(participant.isNearPoint(point))
    {
        point = point.getPointByVector(contrast_vector);
        ++countP_cv;
        ++total_point;

    }

    return total_point;
}

//return true if computer made move
bool blockPlayerCombination(const Participant &player, Participant &computer)
{
    for(int start_point{ 0 }; start_point < player.getCountPoints(); ++start_point)
    {
        for(int vector{ 0 }; vector < static_cast<int>(Vector::MAX_VECTORS); ++vector)
        {
            PointXY near_point{ player[start_point].getPointByVector(static_cast<Vector>(vector)) };
            if(near_point == PointXY(0,0))
                continue;

            if(player.isNearPoint(near_point))
            {
                int countP_v{ 0 };
                int countP_cv{ 0 };

                if(calculatePoints(player[start_point], player, static_cast<Vector>(vector), countP_v, countP_cv) >= 3)
                {
                    PointXY tmp_point(player[start_point]);

                    if(countP_v > 0)
                    {
                        for(int i{ 0 }; i <= countP_v; ++i)
                            tmp_point = tmp_point.getPointByVector(static_cast<Vector>(vector));

                        if(!computer.isContainPoint(tmp_point) && !player.isContainPoint(tmp_point) && tmp_point != PointXY(0,0))
                        {
                            computer.makeMove(tmp_point);
                            return true;
                        }
                    }

                    tmp_point = player[start_point];
                    Vector contrast_vector = SupportFunctions::getContrastVector(static_cast<Vector>(vector));

                    if(countP_cv > 0)
                    {
                        for(int i{ 0 }; i < countP_cv; ++i)
                            tmp_point = tmp_point.getPointByVector(static_cast<Vector>(contrast_vector));

                        if(!computer.isContainPoint(tmp_point) && !player.isContainPoint(tmp_point) && tmp_point != PointXY(0,0))
                        {
                            computer.makeMove(tmp_point);
                            return true;
                        }
                    }
                }
            }
        }
    }

    return false;
}
int main()
{
    drawGameField();
    Participant player{ Constants::player_sign };
    Participant computer{ Constants::computer_sign };

    for(int i{ 0 }; i < 6; ++i)
        player.makeMove();

    for(int i{ 0 }; i < 2; ++i)
        blockPlayerCombination(player, computer);

     makeSpace();
     SupportFunctions::setColor(Constants::color_black, Constants::color_white);
     std::cout << "Player's points\n";
    for(int point{ 0 }; point < player.getCountPoints(); ++ point)
        std::cout << player[point];


    std::cout << '\n';
    std::cout << "Computer's points\n";
    for(int point{ 0 }; point < computer.getCountPoints(); ++ point)
        std::cout << computer[point];

    makeSpace();
    return 0;
}
