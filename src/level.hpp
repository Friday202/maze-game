#pragma once

#include <vector>
#include <string>

#include "types.hpp"

class GameManager; 

class Level
{
public:
    Level(const std::string& name, const int size, GameManager* gameManager);
    virtual ~Level() = default;

public:
    virtual void drawLevel();

    void movePlayer(Point2D delta);
    
    void resetPlayerPosition();

protected:
    virtual void createLayout();    
    virtual void applyBounds(Point2D& delta);
    virtual bool hasHitWall(const Point2D& pos);
    virtual bool hasReachedExit(const Point2D& pos);

    virtual void setPlayerPosition(const Point2D& newPos);

private:
    const int numOfWalls = 6; 

    const std::string m_name;
    const int m_size;       
    
    Point2D m_player {0, 0};

    std::vector<std::vector<std::string>> m_layout;

    GameManager* m_gameManager = nullptr; 

public:
    std::string getLevelName() const { return m_name; }
    Point2D getPlayerPosition() const { return m_player; }
    int getLevelSize() const { return m_size; }    
};