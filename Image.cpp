#include "Image.h"

#include <SDL_image.h>
#include <stdexcept>

namespace lyt {
    Image::Image() {}

    Image::~Image() {
        if (texture) SDL_DestroyTexture(texture);
        IMG_Quit();
    }

    void Image::draw() {
        this->renderer->copy(texture, nullptr, &rect);
        SDL_FreeSurface(surface);
    }

    void Image::setImage(const std::string &filePath, Renderer *renderer, SDL_Rect rect, SDL_BlendMode blendMode,
                         Uint8 alpha) {
        this->rect = rect;
        this->blendMode = blendMode;
        this->alpha = alpha;
        this->filePath = filePath;
        this->renderer = renderer;
        SDL_Surface *surface = IMG_Load(filePath.c_str());
        if (surface == nullptr) {
            throw std::runtime_error("Failed to load image: " + std::string(SDL_GetError()));
        }
        if (texture) SDL_DestroyTexture(texture);
        texture = SDL_CreateTextureFromSurface(renderer->get(), surface);
        if (!texture) {
            throw std::runtime_error(SDL_GetError());
        }
        SDL_SetTextureBlendMode(texture, blendMode);
        SDL_SetTextureAlphaMod(texture, alpha);
    }
}  // namespace lyt
