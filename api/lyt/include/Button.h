//
// Created by restarhalf on 25-5-31.
//

#ifndef BUTTON_H
#define BUTTON_H
#include <Image.h>
#include <Renderer.h>
#include <SDL.h>
#include <Text.h>
namespace lyt
{
    class Button
    {
    private:
        // 按钮矩形区域
        SDL_Rect rect;
        // 按钮是否被点击
        bool isClicked = false;
        // 按钮是否被按下
        bool isPressed = false;
        // 按钮是否被释放
        bool isReleased = true;
        // 纹理
        SDL_Texture *texture = nullptr;
        // surface
        SDL_Surface *surface = nullptr;
        // 按钮颜色
        SDL_Color buttonColor;
        // BlEND mode
        SDL_BlendMode blendMode = SDL_BLENDMODE_BLEND;
        // 文字颜色
        SDL_Color textColor;
        // 字体
        TTF_Font *font = nullptr;
        // 整个字
        Text text;
        // 渲染器
        Renderer *renderer = nullptr;
        // 透明度
        Uint8 alpha = 255;
        // 图片
        std::string filePath;
        Image       image;


    public:
        Button() = default;

        ~Button() = default;

        [[nodiscard]] bool isButtonClicked() const;
        [[nodiscard]] bool isButtonReleased() const;
        [[nodiscard]] bool isButtonPressed() const;
        void draw();

        void drawwithImage();

        void handleEvent(SDL_Event &event);

        void setButton(int x, int y, int w, int h, SDL_Color color);

        void setButton(SDL_Rect rect, SDL_Color color);

        void setText(const std::string &text, TTF_Font *font, SDL_Color color, Renderer *renderer,
                     SDL_BlendMode blendMode, Uint8 alpha);
        void setButtonwithImage(const std::string &filePath, Renderer *renderer, SDL_Rect rect,
                                SDL_BlendMode blendMode = SDL_BLENDMODE_BLEND, Uint8 alpha = 255);
    };
}  // namespace lyt

#endif  // BUTTON_H
