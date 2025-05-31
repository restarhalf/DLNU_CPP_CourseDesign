//
// Created by restarhalf on 2025/5/29.
//

#ifndef TEXT_H
#define TEXT_H
#include <SDL_egl.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include "Renderer.h"

namespace lyt {
    class Text {
    private:
        //字体
        SDL_Texture *texture;
        SDL_Rect rect;
        SDL_Color color;
        TTF_Font *font;
        SDL_Surface *surface;
        SDL_BlendMode blendMode;
        Uint8 alpha;
        std::string text;
        Renderer *renderer;

    public:
        //构造函数和析构函数
        Text();

        ~Text();

        [[nodiscard]] SDL_Texture *get_texture() const;

        void set_texture(SDL_Texture *const texture);

        [[nodiscard]] SDL_Rect get_rect() const;

        void set_rect(const SDL_Rect &rect);

        [[nodiscard]] SDL_Color get_color() const;

        void set_color(const SDL_Color &color);

        [[nodiscard]] TTF_Font *get_font() const;

        void set_font(TTF_Font *const font);

        [[nodiscard]] SDL_Surface *get_surface() const;

        void set_surface(SDL_Surface *const surface);

        [[nodiscard]] SDL_BlendMode get_blend_mode() const;

        void set_blend_mode(const SDL_BlendMode blend_mode);

        [[nodiscard]] std::string get_text() const;

        void set_text(const std::string &text);

        void set_All(Renderer *render, SDL_Rect rect, SDL_Color color, TTF_Font *font, SDL_BlendMode
                     blendMode, std::string text, Uint8 alpha);

        void flush();

        //绘制文字
        void draw();
    };
}


#endif //TEXT_H
