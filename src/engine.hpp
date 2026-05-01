#pragma once

#include "game_manager.hpp"
#include "player_controller.hpp"
#include "types.hpp"

#include <vector>
#include <unordered_map>
#include <memory>

struct ActionBinding 
{   
    InputAction action;
    std::string description;
    GameState displayState; 
    std::vector<std::string> args;    
};

class Engine
{
public:     
    Engine();
    virtual ~Engine();

public:
    /* Outer init if class gets extended */
    virtual void init();

    /* Main game loop */
    int run();    

protected:  
    virtual void engineStart();  
          
    virtual void initializeInputMap();
    virtual bool handleInput(const ActionBinding& binding, const std::vector<std::string>& args);   
    
    virtual bool handleNewGame(const std::vector<std::string>& args);

protected:
    void engineStop();
    void printAviableActions();

private:
    std::unique_ptr<GameManager> m_gameManager = nullptr;
    std::unique_ptr<PlayerController> m_playerController = nullptr;

    // Input handling 
    std::unordered_map<std::string, ActionBinding> m_inputMap;
};