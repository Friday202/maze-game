#include "player_controller.hpp"

#include "level.hpp"
#include <iostream>

void PlayerController::handleMoveInput(InputAction direction, Level* level)
{
    MoveDirection dir = MoveDirection::MD_Up;
    switch(direction)
    {
    case InputAction::IA_Move_Up: dir = MoveDirection::MD_Up; break;
    case InputAction::IA_Move_Down: dir = MoveDirection::MD_Down; break;
    case InputAction::IA_Move_Left: dir = MoveDirection::MD_Left; break;
    case InputAction::IA_Move_Right: dir = MoveDirection::MD_Right; break;
    default:
        std::cerr << "PlayerController::handleMoveInput: Invalid move direction input!" << std::endl;
        return;
    }
    
    applyMovement(dir, level);
}

void PlayerController::applyMovement(PlayerController::MoveDirection direction, Level* level)
{
    if (!level || !bInputEnabled) return;    

    Point2D delta = {0, 0}; 

    switch (direction)
    {
    case MoveDirection::MD_Up:
        delta.y--;
        break;
    case MoveDirection::MD_Down:
        delta.y++;
        break;
    case MoveDirection::MD_Left:
        delta.x--;
        break;
    case MoveDirection::MD_Right:        
        delta.x++;
        break;

    default:
        break;
    }

    level->movePlayer(delta); 
    level->drawLevel();       
}

void PlayerController::enableInput()
{
    bInputEnabled = true; 
}

void PlayerController::disableInput()
{
    bInputEnabled = false; 
}