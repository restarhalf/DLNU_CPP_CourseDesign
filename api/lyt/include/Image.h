//
// Created by restarhalf on 2025/5/29.
//

#ifndef IMAGE_H
#define IMAGE_H
#include <Renderer.h>
#include <SDL.h>
#include <SDL_image.h>
#include <bits/stdc++.h>

namespace lyt
{
    class Image
    {
        SDL_Texture*  texture = nullptr;
        SDL_Surface*  surface = nullptr;
        SDL_Rect      rect;
        SDL_Color     color;
        std::string   filePath;
        Renderer*     renderer;
        SDL_BlendMode blendMode = SDL_BLENDMODE_BLEND;
        Uint8         alpha     = 255;

    public:
        Image();

        ~Image();

        void draw();

        void setImage(const std::string& filePath, Renderer* renderer, SDL_Rect rect, SDL_BlendMode blendMode,
                      Uint8 alpha);
        [[nodiscard]] SDL_Rect      getRect() const;
        void                        setRect(const SDL_Rect& rect);
        [[nodiscard]] SDL_Color     getColor() const;
        void                        setColor(const SDL_Color& color);
        [[nodiscard]] std::string   getFilepath() const;
        void                        setFilepath(const std::string& file_path);
        [[nodiscard]] Renderer*     getRenderer() const;
        void                        setRenderer(Renderer* renderer);
        [[nodiscard]] SDL_BlendMode getBlendmode() const;
        void                        setBlendmode(SDL_BlendMode blend_mode);
        [[nodiscard]] Uint8         getAlpha() const;
        void                        setAlpha(Uint8 alpha);
    };
}  // namespace lyt
#endif  // IMAGE_H
