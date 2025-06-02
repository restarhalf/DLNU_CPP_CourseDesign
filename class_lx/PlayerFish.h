#ifndef PLAYERFISH_H
#define PLAYERFISH_H

#include "Fish.h"

namespace lx {

    class PlayerFish : public Fish
    {
    public:
        PlayerFish(SDL_Renderer* renderer, int x, int y, int width, int height);

        void update(int windowW, int windowH) override;

        bool tryEat(Fish& other) override;

        void moveUp(bool pressed);
        void moveDown(bool pressed);
        void moveLeft(bool pressed);
        void moveRight(bool pressed);

        bool isDead() const;

    private:
        bool movingUp, movingDown, movingLeft, movingRight;
        int speed;
        bool dead;
    };

} // namespace lx

#endif
