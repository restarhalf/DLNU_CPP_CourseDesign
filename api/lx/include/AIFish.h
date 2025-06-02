#ifndef AIFISH_H
#define AIFISH_H

#include "Fish.h"

namespace lx {

    class AIFish : public Fish
    {
    public:
        AIFish(SDL_Renderer* renderer, int x, int y, int width, int height);

        void update(int windowW, int windowH) override;

        bool tryEat(Fish& other) override;

    private:
        float vx;

        void reverseDirection();
    };

} // namespace lx

#endif
