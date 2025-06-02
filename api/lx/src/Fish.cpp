#include "Fish.h"

namespace lx {

    Fish::Fish(lyt::Renderer* renderer, int x, int y, int width, int height)
        : renderer(renderer), x(x), y(y), width(width), height(height)
    {
        size = (width + height) / 2;
        rect = { x, y, width, height };
    }

    void Fish::update(int windowW, int windowH)
    {
        rect = { x, y, width, height };
    }

    void Fish::render()
    {
        SDL_SetRenderDrawColor(renderer->get(), 0, 0, 255, 255);
        SDL_RenderFillRect(renderer->get(), &rect);
    }

    bool Fish::isCollide(const Fish& other) const
    {
        return SDL_HasIntersection(&rect, &other.rect);
    }

    bool Fish::tryEat(Fish& other)
    {
        if (this != &other && isCollide(other) && size > other.size)
        {
            size += other.size *0.1;
            width = height = size;
            rect.w = width;
            rect.h = height;
            return true;
        }
        return false;
    }

} // namespace lx
