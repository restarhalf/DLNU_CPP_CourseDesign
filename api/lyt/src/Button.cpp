//
// Created by restarhalf on 25-5-31.
//

#include "Button.h"
namespace lyt
{
    bool Button::isButtonClicked() const
    {
        if (isClicked)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    bool Button::isButtonReleased() const
    {
        if (isReleased)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    bool Button::isButtonPressed() const
    {
        if (isPressed)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void Button::draw()
    {
        // 保存当前渲染器状态
        Uint8 r, g, b, a;
        SDL_GetRenderDrawColor(renderer->get(), &r, &g, &b, &a);
        SDL_BlendMode currentBlendMode;
        SDL_GetRenderDrawBlendMode(renderer->get(), &currentBlendMode);

        // 设置按钮颜色
        SDL_SetRenderDrawColor(renderer->get(), buttonColor.r, buttonColor.g, buttonColor.b, buttonColor.a);
        SDL_SetRenderDrawBlendMode(renderer->get(), blendMode);

        // 圆角半径
        int radius = 15;

        // 绘制中间矩形
        SDL_Rect centerRect = {rect.x + radius, rect.y, rect.w - 2 * radius, rect.h};
        SDL_RenderFillRect(renderer->get(), &centerRect);

        // 绘制左右矩形
        SDL_Rect leftRect  = {rect.x, rect.y + radius, radius, rect.h - 2 * radius};
        SDL_Rect rightRect = {rect.x + rect.w - radius, rect.y + radius, radius, rect.h - 2 * radius};
        SDL_RenderFillRect(renderer->get(), &leftRect);
        SDL_RenderFillRect(renderer->get(), &rightRect);

        // 绘制四个圆角
        for (int w = 0; w < radius; w++)
        {
            for (int h = 0; h < radius; h++)
            {
                float pk = sqrt((float) ((radius - w) * (radius - w) + (radius - h) * (radius - h)));
                if (pk <= radius)
                {
                    // 左上角
                    SDL_RenderDrawPoint(renderer->get(), rect.x + w, rect.y + h);
                    // 右上角
                    SDL_RenderDrawPoint(renderer->get(), rect.x + rect.w - w - 1, rect.y + h);
                    // 左下角
                    SDL_RenderDrawPoint(renderer->get(), rect.x + w, rect.y + rect.h - h - 1);
                    // 右下角
                    SDL_RenderDrawPoint(renderer->get(), rect.x + rect.w - w - 1, rect.y + rect.h - h - 1);
                }
            }
        }
        // 绘制文本
        SDL_SetTextureAlphaMod(texture, alpha);
        renderer->copy(texture, nullptr, &rect);
        text.draw();

        // 还原渲染器状态
        SDL_SetRenderDrawColor(renderer->get(), r, g, b, a);
        SDL_SetRenderDrawBlendMode(renderer->get(), currentBlendMode);
    }
    void Button::drawwithImage()
    {
        if (isClicked || isPressed)
        {
            // 按下时降低图片的透明度来实现变暗效果
            image.setAlpha(alpha * 0.6);
        }
        else
        {
            // 未按下时使用正常透明度
            image.setAlpha(alpha);
        }
        image.draw();
    }

    void Button::handleEvent(SDL_Event &event)
    {
        bool isInside = false;
        int mouseX, mouseY;

        // 重置released状态（应该只持续一帧）
        isReleased = false;

        switch (event.type) {
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    mouseX = event.button.x;
                    mouseY = event.button.y;
                    isInside = (mouseX >= rect.x && mouseX <= rect.x + rect.w &&
                               mouseY >= rect.y && mouseY <= rect.y + rect.h);
                    if (isInside) {
                        isClicked = true;
                        isPressed = true;
                    }
                }
                break;

            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    mouseX = event.button.x;
                    mouseY = event.button.y;
                    isInside = (mouseX >= rect.x && mouseX <= rect.x + rect.w &&
                               mouseY >= rect.y && mouseY <= rect.y + rect.h);

                    if (isInside && isPressed) {
                        isReleased = true;
                    }
                    isClicked = false;
                    isPressed = false;
                }
                break;

            case SDL_MOUSEMOTION:
                mouseX = event.motion.x;
                mouseY = event.motion.y;
                isInside = (mouseX >= rect.x && mouseX <= rect.x + rect.w &&
                           mouseY >= rect.y && mouseY <= rect.y + rect.h);

                if (isInside) {
                    if (!isClicked && !isPressed) {
                        image.setAlpha(alpha * 0.8);
                    }
                } else {
                    isClicked = false;
                    if (!isPressed) {
                        image.setAlpha(alpha);
                    }
                }
                break;
        }
    }

    void Button::setButton(int x, int y, int w, int h, SDL_Color color)
    {
        rect.x      = x;
        rect.y      = y;
        rect.w      = w;
        rect.h      = h;
        image.setRect(rect);
        buttonColor = color;  // 设置按钮颜色
        isClicked   = false;  // 重置点击状态
    }

    void Button::setButton(SDL_Rect rect, SDL_Color color)
    {
        this->rect  = rect;
        image.setRect(rect);
        buttonColor = color;  // 设置按钮颜色
        isClicked   = false;  // 重置点击状态
    }

    void Button::setText(const std::string &text, TTF_Font *font, SDL_Color color, Renderer *renderer,
                         SDL_BlendMode blendMode = SDL_BLENDMODE_BLEND, Uint8 alpha = 255)
    {
        this->font      = font;
        this->textColor = color;
        this->renderer  = renderer;
        this->blendMode = blendMode;
        this->alpha     = alpha;

        // 获取文本尺寸
        int textWidth, textHeight;
        TTF_SizeText(font, text.c_str(), &textWidth, &textHeight);

        // 计算缩放比例以适应按钮
        double scaleX = rect.w * 0.8 / textWidth;  // 留出20%的边距
        double scaleY = rect.h * 0.7 / textHeight;  // 选择较小的缩放比例以保持宽高比

        // 计算缩放后的文本尺寸
        int scaledWidth  = static_cast<int>(textWidth * scaleX);
        int scaledHeight = static_cast<int>(textHeight * scaleY);

        // 计算居中位置
        SDL_Rect centeredRect = {rect.x + (rect.w - scaledWidth) / 2,  // 水平居中
                                 rect.y + (rect.h - scaledHeight) / 2,  // 垂直居中
                                 scaledWidth, scaledHeight};

        this->text.setAll(renderer, centeredRect, color, font, blendMode, text, alpha);
    }

    void Button::setButtonwithImage(const std::string &filePath, Renderer *renderer, SDL_Rect rect,
                                    SDL_BlendMode blendMode, Uint8 alpha)
    {
        this->rect      = rect;
        this->blendMode = blendMode;
        this->alpha     = alpha;
        this->filePath  = filePath;
        this->renderer  = renderer;
        image.setImage(filePath, renderer, rect, blendMode, alpha);
    }
}  // namespace lyt
