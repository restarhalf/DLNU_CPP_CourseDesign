#include "Renderer.h"

#include <bits/stdc++.h>
#include <stdexcept>

namespace lyt {
    Renderer::Renderer(SDL_Renderer *renderer) { renderer_ = renderer; }

    Renderer::Renderer() { renderer_ = nullptr; };

    Renderer::Renderer(const Window *window, bool vsync) {
        Uint32 flags = SDL_RENDERER_ACCELERATED;
        if (vsync) flags |= SDL_RENDERER_PRESENTVSYNC;

        renderer_ = SDL_CreateRenderer(const_cast<SDL_Window *>(window->get()), -1, flags);
        if (!renderer_) {
            throw std::runtime_error(SDL_GetError());
        }

        SDL_SetRenderDrawColor(renderer_, 1000, 1000, 1000, 255);
    }

    Renderer::~Renderer() {
        if (renderer_) {
            SDL_DestroyRenderer(renderer_);
        }
    }

    void Renderer::clear() const { SDL_RenderClear(renderer_); }

    void Renderer::present() const { SDL_RenderPresent(renderer_); }

    int Renderer::copy(SDL_Texture *texture, SDL_Rect *src, SDL_Rect *dst) const {
        return SDL_RenderCopy(renderer_, texture, src, dst);
    }
}  // namespace lyt
