#include "Image.h"
#include <SDL_image.h>
#include <stdexcept>

namespace lyt {

    Image::Image(){
    }

    Image::~Image() {
        if (texture) SDL_DestroyTexture(texture);
        IMG_Quit();
    }

    void Image::drawImage(const char *filePath,Renderer * renderer, SDL_Rect dst) {
        SDL_Surface *surface = IMG_Load_RW(SDL_RWFromFile(filePath, "rb"), 1);
        if (surface == NULL) {
            throw std::runtime_error("Failed to load image: " + std::string(SDL_GetError()));
        }
        createTexture(surface, renderer);
        renderer->copy(texture,nullptr,&dst);
        SDL_FreeSurface(surface);
    }

    void Image::createTexture(SDL_Surface *surface,Renderer * renderer) {
        if (texture) SDL_DestroyTexture(texture);
        texture = SDL_CreateTextureFromSurface(renderer->get(), surface);
        if (!texture) {
            throw std::runtime_error(SDL_GetError());
        }
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
