#ifndef IMAGE_H
#define IMAGE_H
#include <SDL.h>
#include <SDL_image.h>
#include <stdexcept>

#include "Renderer.h"
#include "Text.h"

namespace lyt
{
    class Image
    {
        SDL_Texture  *texture = nullptr;
        SDL_Surface  *surface = nullptr;
        SDL_Rect      rect;
        SDL_Color     color;
        std::string   filePath;
        Renderer     *renderer;
        SDL_BlendMode blendMode = SDL_BLENDMODE_BLEND;
        Uint8         alpha     = 255;

    public:
        Image();

        ~Image();

        void draw();

        void setImage(const std::string &filePath, Renderer *renderer, SDL_Rect rect, SDL_BlendMode blendMode,
                      Uint8 alpha);
    };
}  // namespace lyt
#endif  // IMAGE_H
