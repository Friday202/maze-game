#include "engine.hpp"
#include <iostream>
#include <string>
#include <charconv>

Engine::Engine()
{
    m_playerController = std::make_unique<PlayerController>(); 
    m_gameManager = std::make_unique<GameManager>(m_playerController.get());       
}

void Engine::init()
{
    engineStart();

    initializeInputMap();  
    
    printAviableActions();
}

Engine::~Engine()
{
    engineStop();
}

void Engine::initializeInputMap()
{    
    m_inputMap["W"] = { InputAction::IA_Move_Up,       "Move Up",       GameState::GS_Playing   };
    m_inputMap["A"] = { InputAction::IA_Move_Left,     "Move Left",     GameState::GS_Playing   };
    m_inputMap["S"] = { InputAction::IA_Move_Down,     "Move Down",     GameState::GS_Playing   };
    m_inputMap["D"] = { InputAction::IA_Move_Right,    "Move Right",    GameState::GS_Playing   };

    m_inputMap["R"] = { InputAction::IA_Restart_Game,  "Restart Game",  GameState::GS_Game_Over   };
    m_inputMap["L"] = { InputAction::IA_Load_Game,     "Load Game",     GameState::GS_Menu,     { "Insert game name" }  };    
    m_inputMap["N"] = { InputAction::IA_New_Game,      "New Game",      GameState::GS_Menu,     { "Insert layout size (16 > N > 3)", "Insert game name" }   };

    m_inputMap["H"] = { InputAction::IA_All_Games,     "Show aviable games",    GameState::GS_Menu  };    

    m_inputMap["X"] = { InputAction::IA_Quit_Game,     "Quit Game",     GameState::GS_Menu     };      
}

void Engine::engineStart()
{
    std::cout << "Welcome to The Maze Game!\n" << "To exit the game at any time press [X] or [Ctrl] + [C] or ";
#ifdef _WIN32
    std::cout << "[Ctrl] + [Z] and [Enter] on Windows." << std::endl;
#else   
    std::cout << "[Ctrl] + [D] on Linux." << std::endl;
#endif
}

void Engine::engineStop()
{
    std::cout << "Thank you, for playing the game!" << std::endl;
}

int Engine::run() 
{    
    std::string input;     

    while (std::cin >> input)
    {                    
        if (!m_inputMap.contains(input)) continue;

        const ActionBinding& binding = m_inputMap.at(input);

        std::vector<std::string> args;
        args.reserve(binding.args.size());

        for (const auto& argName : binding.args)
        {
            std::cout << argName << ": ";
            std::string arg;
            if (!(std::cin >> arg)) return 0;
            args.push_back(std::move(arg));
        }          

        if (handleInput(binding, args)) break;

        printAviableActions();
    }

    return 0;
}

void Engine::printAviableActions()
{
    std::cout << "---------------------\n";
    std::cout << "Select one of the aviable actions:\n";
    for (const auto& [key, binding] : m_inputMap)
    {   
        if (m_gameManager->getGameState() < binding.displayState) continue;
        std::cout << '[' << key << "] - " << binding.description << '\n';              
    }
    std::cout << "---------------------" << std::endl;
}

bool Engine::handleInput(const ActionBinding& binding, const std::vector<std::string>& args)
{   
    bool bShouldQuit = false;

    if (args.size() < binding.args.size())
    {
        std::cerr << "Engine::handleInput: Insufficient args for action with description: " << binding.description << '\n';
        return bShouldQuit; 
    }    

    switch (binding.action)
    {           
        case InputAction::IA_Move_Up:
        case InputAction::IA_Move_Down:
        case InputAction::IA_Move_Left:
        case InputAction::IA_Move_Right:
            m_playerController->handleMoveInput(binding.action, m_gameManager->getCurrentLevel()); break;
       
        case InputAction::IA_Restart_Game: m_gameManager->restartCurrentGame(); break;           
        case InputAction::IA_New_Game: handleNewGame(args); break;         
        case InputAction::IA_Load_Game: m_gameManager->loadExsistingGame(args[0]); break;              
        case InputAction::IA_All_Games: m_gameManager->printAvailableGames(); break; 

        case InputAction::IA_Quit_Game: bShouldQuit = true; break;  
        case InputAction::IA_Invalid: /*siliently ignore invalid actions*/ break; 

        default: std::cerr << "Engine::handleInput: Invalid action or action not implemented!\n";
    }     
    
    return bShouldQuit; 
}

bool Engine::handleNewGame(const std::vector<std::string>& args)
{                
    int size;
    const std::string & s = args[0]; 
    auto result = std::from_chars(s.data(), s.data() + s.size(), size);
    if (result.ec != std::errc()) 
    {
        std::cerr << "Engine::handleNewGame: Error parsing an int!\n";
        return false; 
    }
    
    if (size < 4 || size > 15)
    {
        std::cerr << "Size for grid is too small or too big!\n";
        return false;                              
    }

    m_gameManager->startNewGame(size, args[1]);   
    return true;                                                                                              
}
