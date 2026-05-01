#pragma once

#include "types.hpp"

class Level;

class PlayerController
{
public:
    enum class MoveDirection : int
    {
        MD_Up = 0,
        MD_Down,
        MD_Left,
        MD_Right
    };

    void handleMoveInput(InputAction direction, Level* level);

    void enableInput();
    void disableInput();

protected:
    virtual void applyMovement(PlayerController::MoveDirection direction, Level* level);

private:
    bool bInputEnabled = false; 
};