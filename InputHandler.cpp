#include "InputHandler.h"

namespace lx 
{

    InputHandler::InputHandler(PlayerFish* p) : player(p) {}

    void InputHandler::processInput(char key) 
    {
        if (player) 
        {
            player->handleInput(key);
        }
    }

    void InputHandler::stopMovement() 
    {
        if (player) player->stop();
    }

}
