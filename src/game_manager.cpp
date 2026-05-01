#include "game_manager.hpp"

#include <iostream>
#include <cassert>

 GameManager::GameManager(PlayerController* playerController)
 {
    assert(playerController != nullptr);
    m_playerController = playerController; 
 }

void GameManager::startNewGame(const int size, const std::string& name)
{
    std::cout << "Starting new level with name: \"" << name << "\" and size: " << size << std::endl; 
    if (m_levels.contains(name))
    {
        std::cout << "Level with name \"" << name << "\" already exists!" << std::endl; 
        return;
    }

    std::unique_ptr<Level> level = std::make_unique<Level>(name, size, this);
    m_levels[name] = std::move(level);

    startLevel(m_levels[name].get());              
}

void GameManager::restartCurrentGame()
{
    if (m_gameState < GameState::GS_Game_Over) return;

    if (Level* currentLevel = getCurrentLevel())
    {
        std::cout << "Restarting current level: \"" << currentLevel->getLevelName() << '\"' << std::endl; 

        startLevel(currentLevel);      
    } 
    else
    {
        std::cout << "No current level to restart!" << std::endl; 
    } 
}

void GameManager::loadExsistingGame(const std::string& name)
{
    auto it = m_levels.find(name);
    if (it != m_levels.end())
    {
        std::cout << "Loading existing level: \"" << name << '\"' << std::endl; 

        startLevel(it->second.get());       
    }
    else
    {
        std::cout << "Level with name: \"" << name << "\" not found!" << std::endl; 
    }
}

void GameManager::startLevel(Level* level)
{
    if (!level) return;
    
    m_currentLevelName = level->getLevelName();
    level->resetPlayerPosition();
    level->drawLevel();
    m_gameState = GameState::GS_Playing;
    m_playerController->enableInput();
}

void GameManager::printAvailableGames() const
{
    if (m_levels.size() > 0)
    {
        std::cout << "Available games:\n";

        for (const auto& [key, level]  : m_levels)
        {
            std::cout << "Level: \"" << level->getLevelName() << "\" - Size: " << level->getLevelSize() << '\n'; 
        } 
    }
    else
    {
        std::cout << "No available games found!" << std::endl; 
    }    
}

Level* GameManager::getCurrentLevel() const
{
    auto it = m_levels.find(m_currentLevelName);
    return it != m_levels.end() ? it->second.get() : nullptr;
}

void GameManager::gameOver()
{
    m_gameState = GameState::GS_Game_Over;   
    m_playerController->disableInput();
}