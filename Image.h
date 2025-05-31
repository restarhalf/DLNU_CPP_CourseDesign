#ifndef IMAGE_H
#define IMAGE_H
#include <SDL.h>
#include <SDL_image.h>
#include <stdexcept>

#include "Renderer.h"
#include "Text.h"
#include <SDL_image.h>

namespace lyt {
    class Image :public Text{
        SDL_Texture *texture = nullptr;
    public:

        Image();

        ~Image();

        int getWidth() const;

        int getHeight() const;

        void drawImage(const char *filePath, Renderer *renderer,SDL_Rect rect);
    private:


        void createTexture(SDL_Surface *surface, Renderer *renderer);
    };
}
#endif //IMAGE_H
