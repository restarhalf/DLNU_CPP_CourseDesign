#include "AIFish.h"
#include <cstdlib>

namespace lx {

    AIFish::AIFish(SDL_Renderer* renderer, int x, int y, int width, int height)
        : Fish(renderer, x, y, width, height)
    {
        vx = (rand() % 2 == 0) ? 2.0f : -2.0f;
    }

    void AIFish::update(int windowW, int windowH)
    {
        x += static_cast<int>(vx);
        if (x < 0 || x + width > windowW)
        {
            reverseDirection();
            x += static_cast<int>(vx);
        }
        rect.x = x;
        rect.y = y;
        rect.w = width;
        rect.h = height;
    }

    bool AIFish::tryEat(Fish& other)
    {
        if (this != &other && isCollide(other) && size > other.getSize())
        {
            size += other.getSize() / 3;
            width = height = size;
            rect.w = width;
            rect.h = height;
            return true;
        }
        return false;
    }

    void AIFish::reverseDirection()
    {
        vx = -vx;
    }

} // namespace lx
