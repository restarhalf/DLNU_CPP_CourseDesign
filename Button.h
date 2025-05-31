//
// Created by restarhalf on 25-5-31.
//

#ifndef BUTTON_H
#define BUTTON_H
#include "Renderer.h"
#include "SDL.h"
#include "SDL_ttf.h"
#include "Text.h"

namespace lyt {
    class Button {
    private:
        // 按钮矩形区域
        SDL_Rect rect;
        // 按钮是否被点击
        bool isClicked;
        //纹理
        SDL_Texture *texture = nullptr;
        // surface
        SDL_Surface *surface = nullptr;
        //按钮颜色
        SDL_Color buttonColor;
        //BlEND mode
        SDL_BlendMode blendMode = SDL_BLENDMODE_BLEND;
        //文字颜色
        SDL_Color textColor;
        //字体
        TTF_Font *font = nullptr;
        //整个字
        Text text;

    public:
        Button() = default;

        ~Button() = default;

        bool isButtonClicked() const;

        void draw(Renderer *renderer);

        void handleEvent(const SDL_Event &event);

        void setButton(int x, int y, int w, int h, SDL_Color color);

        void setButton(SDL_Rect rect, SDL_Color color);

        void setText(const std::string &text, TTF_Font *font, SDL_Color color, Renderer *renderer,
                     SDL_BlendMode blendMode, Uint8 alpha);
    };
} // lyt

#endif //BUTTON_H
