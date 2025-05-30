#include "Image.h"
#include <SDL_image.h>
#include <stdexcept>

namespace lyt {
    Image::Image(const char *filePath, Renderer *renderer) : renderer(renderer) {
        loadImage(filePath);
    }

    Image::~Image() {
        if (texture) SDL_DestroyTexture(texture);
    }

    void Image::loadImage(const char *filePath) {
        SDL_Surface *surface = IMG_Load(filePath);
        if (surface == NULL) {
            throw std::runtime_error("Failed to load image: " + std::string(SDL_GetError()));
        }
        createTexture(surface);
        SDL_FreeSurface(surface);
    }

    void Image::createTexture(SDL_Surface *surface) {
        if (texture) SDL_DestroyTexture(texture);
        texture = SDL_CreateTextureFromSurface(renderer->get(), surface);
        if (!texture) {
            throw std::runtime_error(SDL_GetError());
        }
    }

    SDL_Texture *Image::getTexture() const {
        return texture;
    }

    int Image::getWidth() const {
        int w;
        SDL_QueryTexture(texture, nullptr, nullptr, &w, nullptr);
        return w;
    }

    int Image::getHeight() const {
        int h;
        SDL_QueryTexture(texture, nullptr, nullptr, nullptr, &h);
        return h;
    }
}
