#include "level.hpp"

#include "game_manager.hpp"

#include <iostream>
#include <set>
#include <cassert>

Level::Level(const std::string& name, const int size, GameManager* gameManager) 
    : m_name(name), m_size(size), m_gameManager(gameManager)
{
    assert(m_size > 3 && m_size < 16);

    createLayout();
}

void Level::createLayout()
{
    // creates level of NxN puts in entities player, end and walls   
    std::set<Point2D> walls;       
    while (walls.size() < numOfWalls)
    {
        int x = rand() % m_size;
        int y = rand() % m_size;

        if ((x == 0 && y == 0) || (x == m_size - 1 && y == m_size - 1))
            continue;

        walls.insert({x, y}); 
    }

    // Build the layout - only thing that moves is the player 
    m_layout.resize(m_size, std::vector<std::string>(m_size, " . "));
    m_layout[m_player.y][m_player.x] = " P ";
    m_layout[m_size -1][m_size -1] = " X ";

    for (const auto& w : walls) 
    {
        m_layout[w.y][w.x] = " W ";
    }    
}

void Level::drawLevel()
{       
    for (int i = 0; i <= m_size ; ++i) 
    {
        std::cout << " - ";
    }

    std::cout << '\n';
    
    for (int y = 0; y < m_size; ++y) 
    {        
        for (int x = 0; x < m_size; ++x) 
        { 
            if (x == 0)
                std::cout << "|";

            std::cout << m_layout[y][x];       

            if (x == m_size - 1)
                std::cout << "|";
        }
        std::cout << '\n';
    }

    for (int i = 0; i <= m_size ; ++i) 
    {
        std::cout << " - ";
    }
    
    std::cout << '\n';
}

void Level::applyBounds(Point2D& delta)
{
    int newX = m_player.x + delta.x;
    int newY = m_player.y + delta.y;

    if (newX < 0 || newX >= m_size)
    {
        delta.x = 0; 
    }

    if (newY < 0 || newY >= m_size)
    {
        delta.y = 0; 
    }      
}

bool Level::hasHitWall(const Point2D& pos)
{
    if (m_layout[pos.y][pos.x] == " W ")
    {               
        return true;        
    }
    return false; 
}

bool Level::hasReachedExit(const Point2D& pos)
{
    if (m_layout[pos.y][pos.x] == " X ")
    {               
        return true;        
    }
    return false; 
}

void Level::movePlayer(Point2D delta)
{
    applyBounds(delta);

    Point2D oldPos = m_player;
    Point2D newPos = m_player + delta; 

    if (hasHitWall(newPos))
    {
        std::cout << "You hit a wall! Game over." << std::endl;
        m_gameManager->gameOver();
        return; 
    }

    if (hasReachedExit(newPos))
    {
        std::cout << "You win! Game over." << std::endl;
        m_gameManager->gameOver();
        return; 
    }
    
    setPlayerPosition(newPos);
}

void Level::resetPlayerPosition()
{
    setPlayerPosition({0,0});
}

void Level::setPlayerPosition(const Point2D& newPos)
{
    m_layout[m_player.y][m_player.x] = " . ";

    m_player = newPos; 

    m_layout[m_player.y][m_player.x] = " P ";
}