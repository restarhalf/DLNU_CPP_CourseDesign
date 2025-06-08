//
// Created by restarhalf on 2025/5/29.
//

#include "Text.h"

namespace lyt
{
    // 析构函数，清理资源
    Text::~Text()
    {
        // 按顺序释放资源：纹理、表面、字体
        if (texture) SDL_DestroyTexture(texture);
        if (surface) SDL_FreeSurface(surface);
        if (font) TTF_CloseFont(font);
        texture = nullptr;
        surface = nullptr;
        font    = nullptr;
    }

    // Getters and setters 实现
    SDL_Texture  *Text::getTexture() const { return texture; }
    void          Text::setTexture(SDL_Texture *const texture) { this->texture = texture; }
    SDL_Rect      Text::getRect() const { return rect; }
    void          Text::setRect(const SDL_Rect &rect) { this->rect = rect; }
    SDL_Color     Text::getColor() const { return color; }
    void          Text::setColor(const SDL_Color &color) { this->color = color; }
    TTF_Font     *Text::getFont() const { return font; }
    void          Text::setFont(TTF_Font *const font) { this->font = font; }
    SDL_Surface  *Text::getSurface() const { return surface; }
    void          Text::setSurface(SDL_Surface *const surface) { this->surface = surface; }
    SDL_BlendMode Text::getBlendmode() const { return blendMode; }
    void          Text::setBlendmode(const SDL_BlendMode blend_mode) { blendMode = blend_mode; }
    std::string   Text::getText() const { return text; }
    void          Text::setText(const std::string &text)
    {
        if (this->text != text)
        {
            this->text = text;
            //flush();
        }
    }

    // 设置文本的所有属性并创建纹理
    void Text::setAll(Renderer *render, SDL_Rect rect, SDL_Color color, TTF_Font *font, SDL_BlendMode blendMode,
                      const std::string &text)
    {
        // 设置基本属性
        this->rect      = rect;
        this->color     = color;
        this->font      = font;
        this->blendMode = blendMode;
        this->text      = text;
        this->alpha     = alpha;
        this->renderer  = render;

        // 清理旧的纹理（如果存在）
        if (texture) SDL_DestroyTexture(texture);

        // 使用字体渲染文本
        surface = TTF_RenderUTF8_Blended(this->font, this->text.c_str(), this->color);
        if (!surface)
        {
            SDL_Log("Failed to create surface: %s", SDL_GetError());
            return;
        }

        // 从表面创建纹理
        texture = SDL_CreateTextureFromSurface(render->get(), surface);
        SDL_SetTextureBlendMode(texture, this->blendMode);
        if (!texture)
        {
            SDL_Log("Failed to create texture: %s", SDL_GetError());
            SDL_FreeSurface(surface);
        }
    }

    // 刷新文本纹理
    void Text::flush()
    {
        // 清理并重新创建纹理
        if (texture) SDL_DestroyTexture(texture);
        if (surface) SDL_FreeSurface(surface);
        surface = TTF_RenderUTF8_Blended(font, text.c_str(), color);
        if (!surface)
        {
            SDL_Log("Failed to create surface: %s", SDL_GetError());
            return;
        }

        // 从表面创建新的纹理
        texture = SDL_CreateTextureFromSurface(renderer->get(), surface);
        SDL_SetTextureBlendMode(texture, this->blendMode);
        SDL_SetTextureAlphaMod(texture, this->alpha);
        if (!texture)
        {
            SDL_Log("Failed to create texture: %s", SDL_GetError());
            SDL_FreeSurface(surface);
        }
    }

    // 绘制文本
    void Text::draw() { renderer->copy(texture, nullptr, &rect); }
}  // namespace lyt
