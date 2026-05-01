#pragma once

#include "level.hpp"
#include "types.hpp"
#include "player_controller.hpp"

#include <string>
#include <unordered_map>
#include <memory>

class GameManager
{
public:
    GameManager(PlayerController* playerController);

public:
    void startNewGame(const int size, const std::string& name);
    void restartCurrentGame();  
    void loadExsistingGame(const std::string& name); 

    void printAvailableGames() const;  

    void gameOver();    
    Level* getCurrentLevel() const;

protected:
    void startLevel(Level* level);

private:  
    std::string m_currentLevelName;
    std::unordered_map<std::string, std::unique_ptr<Level>> m_levels;     

    GameState m_gameState = GameState::GS_Menu;

    // Cached reference to player controller - hard pointer 
    PlayerController* m_playerController = nullptr; 

public:
    GameState getGameState() const { return m_gameState; }
};