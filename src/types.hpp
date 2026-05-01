#pragma once

#include <string>

enum class InputAction : int
{
    IA_Invalid = 0,

    IA_Move_Up,
    IA_Move_Down,
    IA_Move_Left,
    IA_Move_Right,

    IA_Restart_Game,    
    IA_New_Game,
    IA_Load_Game,

    IA_All_Games,

    IA_Quit_Game        
};

enum class GameState : int
{
    GS_Menu = 0,
    GS_Game_Over,
    GS_Playing
};

struct Point2D
{
    int x;
    int y;

    Point2D(int x, int y) : x(x), y(y) {}
  
    bool operator<(const Point2D& other) const 
    {
        return std::tie(x, y) < std::tie(other.x, other.y);
    }   

    Point2D operator+(const Point2D& rhs) const
    {
        return Point2D(this->x + rhs.x, this->y + rhs.y);
    }

    Point2D operator-(const Point2D& rhs) const
    {
        return Point2D(this->x - rhs.x, this->y - rhs.y);
    }
};