#include "GameState.h"

namespace lx
{

    GameState::GameState() : current(MENU) {}

    void GameState::setState(State s)
    {
        current = s;
    }

    GameState::State GameState::getState() const
    {
        return current;
    }

    bool GameState::isRunning() const
    {
        return current == RUNNING;
    }

}

