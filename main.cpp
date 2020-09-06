#include "participant.h"
#include "support_functions.h"
#include "pointxy.h"
#include <ctime>
#include <iostream>


enum class ResultGame
{
    PLAYER_WIN,
    COMPUTER_WIN,
    CONTINUE_GAME
};

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
    for(int i{ 0 }; i < Constants::field_width; ++i)
        std::cout << horizontal_line << horizontal_line;
    std::cout << bottom_right_angle << '\n';
}

void makeSpace() { SupportFunctions::setCursor(0, Constants::input_y + 4); }

void countPoints(PointXY &point, const Participant &participant, Vector vector, int &count_p, int &total_points)
{
    while(participant.isNearPoint(point))
    {
        point = point.getPointByVector(vector);
        ++count_p;
        ++total_points;
    }
}

int calculatePoints(const PointXY &start_point, const Participant &participant, Vector vector, int &countP_v, int &countP_cv)
{
    int total_points{ 1 };
    PointXY point(start_point.getPointByVector(vector));

    countPoints(point, participant, vector, countP_v, total_points);

    Vector contrast_vector(SupportFunctions::getContrastVector(vector));
    point = start_point.getPointByVector(contrast_vector);

    countPoints(point, participant, contrast_vector, countP_cv, total_points);

    return total_points;
}

bool computerMakeBlock(int count_p, PointXY &point, const Participant &player,Participant &computer, Vector vector)
{
    if(count_p > 0)
    {
        for(int i{ 0 }; i <= count_p; ++i)
            point = point.getPointByVector(static_cast<Vector>(vector));

        if(!computer.isContainPoint(point) && !player.isContainPoint(point) && point != PointXY(0,0))
        {
            computer.makeMove(point);
            return true;
        }
    }
    return false;
}

//return true if computer made move
bool blockPlayerCombination(const Participant &player, Participant &computer)
{
    for(int start_point{ 0 }; start_point < player.getCountPoints(); ++start_point)
    {
        int random_point(SupportFunctions::getRandomNumber(0, start_point));

        for(int vector{ 0 }; vector < static_cast<int>(Vector::MAX_VECTORS); ++vector)
        {
            PointXY near_point{ player[random_point].getPointByVector(static_cast<Vector>(vector)) };
            if(near_point == PointXY(0,0))
                continue;

            if(player.isNearPoint(near_point))
            {
                int countP_v{ 0 };
                int countP_cv{ 0 };

                if(calculatePoints(player[random_point], player, static_cast<Vector>(vector), countP_v, countP_cv) >= 3)
                {
                    PointXY tmp_point(player[random_point]);

                    if(computerMakeBlock(countP_v, tmp_point, player, computer, static_cast<Vector>(vector)))
                        return true;

                    tmp_point = player[random_point];
                    Vector contrast_vector = SupportFunctions::getContrastVector(static_cast<Vector>(vector));

                    if(computerMakeBlock(countP_cv, tmp_point, player, computer, contrast_vector))
                        return true;
                }
            }
        }
    }
    return false;
}

// look all the computer's points
// look cells which are near computer's point
// if cell is empty that computer sets point
void computerMakeMove(const Participant &player, Participant &computer)
{
    if(computer.getCountPoints() == 0)
    {
        PointXY p;
        do
        {
            int random_vector{ SupportFunctions::getRandomNumber(0, static_cast<int>(Vector::MAX_VECTORS) - 1) };
            p = { player[0].getPointByVector(static_cast<Vector>(random_vector)) };

        } while(p == PointXY(0,0));

        computer.makeMove(p);
        return;
    }


    int random_point{ 0 };
    for(int point{ 0 }; point < computer.getCountPoints(); ++point)
    {
        random_point = SupportFunctions::getRandomNumber(0, computer.getCountPoints() - 1);

        for(int vector{ 0 }; vector < static_cast<int>(Vector::MAX_VECTORS); ++vector)
        {
            PointXY tmp_point(computer[random_point].getPointByVector(static_cast<Vector>(vector)));
            if(tmp_point == PointXY(0,0))
                continue;

            if(!computer.isContainPoint(tmp_point) && !player.isContainPoint(tmp_point))
            {
                computer.makeMove(tmp_point);
                return;
            }
        }
    }
}

int calculateParticipantPoints(const Participant &participant)
{
    int v1{0};
    int v2{0};

    for(int start_point{ 0 }; start_point < participant.getCountPoints(); ++start_point)
    {
        for(int vector{ 0 }; vector < static_cast<int>(Vector::MAX_VECTORS); ++vector)
        {
            int total_points{ 0 };
            total_points = calculatePoints(participant[start_point], participant, static_cast<Vector>(vector),v1,v2);
            if(total_points >= 5)
                return total_points;
        }
    }
    return 0;
}

// look all the participant's points
// calculate all the points from the start point in each direction of the vector
ResultGame analysisGame(const Participant &player, const Participant &computer)
{
    if(calculateParticipantPoints(player)   >= 5)
        return ResultGame::PLAYER_WIN;

    if(calculateParticipantPoints(computer) >= 5)
        return ResultGame::COMPUTER_WIN;

    return ResultGame::CONTINUE_GAME;
}

void printResultGame(ResultGame result)
{

    SupportFunctions::setCursor(0, Constants::field_height + 2);

    switch (result)
    {
        case ResultGame::PLAYER_WIN:   std::cout << "You won!\n"; break;
        case ResultGame::COMPUTER_WIN: std::cout << "Computer won!\n"; break;
    }

    makeSpace();
}

void playGame()
{
    srand(static_cast<unsigned int>(time(0)));
    rand();

    drawGameField();

    Participant player  { Constants::player_sign    };
    Participant computer{ Constants::computer_sign  };
    ResultGame result   { ResultGame::CONTINUE_GAME };

    while (true)
    {
        player.makeMove();
        result = analysisGame(player,computer);
        if(result != ResultGame::CONTINUE_GAME)
            break;

        if(!blockPlayerCombination(player,computer))
            computerMakeMove(player,computer);

        result = analysisGame(player, computer);

        if(result != ResultGame::CONTINUE_GAME)
            break;
    }

    printResultGame(result);
}

int main()
{
    playGame();
    return 0;
}
