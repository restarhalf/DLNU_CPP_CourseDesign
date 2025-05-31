//
// Created by restarhalf on 25-5-31.
//

#include "Button.h"

#include <iostream>

namespace lyt {
    bool Button::isButtonClicked() const {
        if (isClicked) {
            return true;
        } else {
            return false;
        }
    }

    void Button::draw() {
        SDL_SetRenderDrawColor(renderer->get(), buttonColor.r, buttonColor.g, buttonColor.b, buttonColor.a);
        SDL_RenderFillRect(this->renderer->get(), &rect);
        SDL_SetRenderDrawBlendMode(renderer->get(), blendMode);
        SDL_SetTextureAlphaMod(texture, alpha);
        SDL_SetRenderDrawColor(renderer->get(), 0, 0, 0, 225);
        renderer->copy(texture, nullptr, &rect);
        text.draw();
    }

    void Button::handleEvent(SDL_Event &event) {
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            if (event.button.button == SDL_BUTTON_LEFT) {
                int mouseX, mouseY;
                // SDL_GetMouseState(&mouseX, &mouseY);
                mouseX = event.button.x;
                mouseY = event.button.y;
                if (mouseX >= rect.x && mouseX <= rect.x + rect.w && mouseY >= rect.y && mouseY <= rect.y + rect.h) {
                    isClicked = true;
                    std::cout << "Button clicked at (" << mouseX << ", " << mouseY << ")" << std::endl;
                }
            }
        }
    }

    void Button::setButton(int x, int y, int w, int h, SDL_Color color) {
        rect.x = x;
        rect.y = y;
        rect.w = w;
        rect.h = h;
        buttonColor = color; // 设置按钮颜色
        isClicked = false; // 重置点击状态
    }

    void Button::setButton(SDL_Rect rect, SDL_Color color) {
        this->rect = rect;
        buttonColor = color; // 设置按钮颜色
        isClicked = false; // 重置点击状态
    }

    void Button::setText(const std::string &text, TTF_Font *font, SDL_Color color, Renderer *renderer,
                         SDL_BlendMode blendMode = SDL_BLENDMODE_BLEND, Uint8 alpha = 255) {
        this->font = font;
        this->textColor = color;
        this->renderer = renderer;
        this->blendMode = blendMode;
        this->alpha = alpha;
        this->text.setAll(renderer, rect, color, font, blendMode, text, alpha);
    }
} // namespace lyt
