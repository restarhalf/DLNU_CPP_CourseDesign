#include "PlayerFish.h"

namespace lx {

    PlayerFish::PlayerFish(lyt::Renderer* renderer, int x, int y, int width, int height)
        : Fish(renderer, x, y, width, height),
        movingUp(false), movingDown(false),
        movingLeft(false), movingRight(false),
        speed(5), dead(false)
    {
    }

    void PlayerFish::update(int windowW, int windowH)
    {
        if (dead) return;

        if (movingUp) y -= speed;
        if (movingDown) y += speed;
        if (movingLeft) x -= speed;
        if (movingRight) x += speed;

        if (x < 0) x = 0;
        if (x + width > windowW) x = windowW - width;
        if (y < 0) y = 0;
        if (y + height > windowH) y = windowH - height;

        rect.x = x;
        rect.y = y;
        rect.w = width;
        rect.h = height;
    }

    bool PlayerFish::tryEat(Fish& other)
    {
        if (dead) return false;

        if (this != &other && isCollide(other))
        {
            if (size > other.getSize())
            {
                size += other.getSize() * 0.1;
                width = height = size;
                rect.w = width;
                rect.h = height;
                return true;
            }
            else if (size < other.getSize())
            {
                dead = true;
                return false;
            }
        }
        return false;
    }

    void PlayerFish::moveUp(bool pressed) { movingUp = pressed; }
    void PlayerFish::moveDown(bool pressed) { movingDown = pressed; }
    void PlayerFish::moveLeft(bool pressed) { movingLeft = pressed; }
    void PlayerFish::moveRight(bool pressed) { movingRight = pressed; }

    bool PlayerFish::isDead() const { return dead; }

} // namespace lx
