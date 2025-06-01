//
// Created by restarhalf on 2025/5/29.
//

#ifndef TEXT_H
#define TEXT_H
#include <Renderer.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <bits/stdc++.h>

namespace lyt
{
    class Text
    {
    private:
        // 字体
        SDL_Texture  *texture;
        SDL_Rect      rect;
        SDL_Color     color;
        TTF_Font     *font;
        SDL_Surface  *surface;
        SDL_BlendMode blendMode;
        Uint8         alpha;
        std::string   text;
        Renderer     *renderer;

    public:
        // 构造函数和析构函数
        Text();

        ~Text();

        [[nodiscard]] SDL_Texture *getTexture() const;

        void setTexture(SDL_Texture *texture);

        [[nodiscard]] SDL_Rect getRect() const;

        void setRect(const SDL_Rect &rect);

        [[nodiscard]] SDL_Color getColor() const;

        void setColor(const SDL_Color &color);

        [[nodiscard]] TTF_Font *getFont() const;

        void setFont(TTF_Font *font);

        [[nodiscard]] SDL_Surface *getSurface() const;

        void setSurface(SDL_Surface *surface);

        [[nodiscard]] SDL_BlendMode getBlendmode() const;

        void setBlendmode(SDL_BlendMode BlendMode);

        [[nodiscard]] std::string getText() const;

        void setText(const std::string &text);

        void setAll(Renderer *render, SDL_Rect rect, SDL_Color color, TTF_Font *font, SDL_BlendMode blendMode,
                    const std::string &text, Uint8 alpha);
        void flush();
        // 绘制文字
        void draw();
    };
}  // namespace lyt


#endif  // TEXT_H
