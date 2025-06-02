#ifndef FISH_H
#define FISH_H

#include <SDL.h>
#include <lyt_api.h>
namespace lx {

    class Fish
    {
    protected:
        lyt::Renderer* renderer;
        int x, y;
        int width, height;
        int size;
        SDL_Rect rect;
        

    public:
        Fish(lyt::Renderer* renderer, int x, int y, int width, int height);

        virtual ~Fish() = default;

        virtual void update(int windowW, int windowH);

        virtual void render();

        virtual bool tryEat(Fish& other);

        bool isCollide(const Fish& other) const;

        int getSize() const { return size; }
        int getWidth() const { return width; }
        int getHeight() const { return height; }

        SDL_Rect getRect() const { return rect; }
    };

} // namespace lx

#endif
