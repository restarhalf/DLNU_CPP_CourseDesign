#ifndef RENDER_H
#define RENDER_H
#include <SDL.h>

#include "Window.h"

namespace lyt {
    class Renderer {
    public:
        Renderer();

        explicit Renderer(SDL_Renderer *renderer);

        explicit Renderer(const Window *window, bool vsync);

        ~Renderer();

        void clear() const;

        void present() const;

        int copy(SDL_Texture *texture, SDL_Rect *src, SDL_Rect *dst) const;

        [[nodiscard]] SDL_Renderer *get() const { return renderer_; }

    private:
        SDL_Renderer *renderer_ = nullptr;
    };
}  // namespace lyt

#endif  // RENDER_H
