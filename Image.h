#ifndef IMAGE_H
#define IMAGE_H
#include <SDL.h>
#include <SDL_image.h>
#include <stdexcept>

#include "Renderer.h"

namespace lyt {
    class Image {
        SDL_Texture *texture = nullptr;
        Renderer *renderer = nullptr;

    public:
        Image(const char *filePath, Renderer *renderer);

        ~Image();

        SDL_Texture *getTexture() const;

        int getWidth() const;

        int getHeight() const;

    private:
        void loadImage(const char *filePath);

        void createTexture(SDL_Surface *surface);
    };
}
#endif //IMAGE_H
