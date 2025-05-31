//
// Created by restarhalf on 2025/5/29.
//

#include "Text.h"

namespace lyt {
    Text::Text() : texture(nullptr) {
    }

    Text::~Text() {
        if (texture) SDL_DestroyTexture(texture);
    }

    SDL_Texture *Text::get_texture() const {
        return texture;
    }

    void Text::set_texture(SDL_Texture *const texture) {
        this->texture = texture;
    }

    SDL_Rect Text::get_rect() const {
        return rect;
    }

    void Text::set_rect(const SDL_Rect &rect) {
        this->rect = rect;
    }

    SDL_Color Text::get_color() const {
        return color;
    }

    void Text::set_color(const SDL_Color &color) {
        this->color = color;
    }

    TTF_Font *Text::get_font() const {
        return font;
    }

    void Text::set_font(TTF_Font *const font) {
        this->font = font;
    }

    SDL_Surface *Text::get_surface() const {
        return surface;
    }

    void Text::set_surface(SDL_Surface *const surface) {
        this->surface = surface;
    }

    SDL_BlendMode Text::get_blend_mode() const {
        return blendMode;
    }

    void Text::set_blend_mode(const SDL_BlendMode blend_mode) {
        blendMode = blend_mode;
    }

    std::string Text::get_text() const {
        return text;
    }

    void Text::set_text(const std::string &text) {
        this->text = text;
    }

    void Text::set_All(Renderer *render, SDL_Rect rect, SDL_Color color, TTF_Font *font, SDL_BlendMode blendMode,
                       std::string text, Uint8 alpha) {
        this->rect = rect;
        this->color = color;
        this->font = font;
        this->blendMode = blendMode;
        this->text = text;
        this->alpha = alpha;
        renderer = render;
        if (texture) SDL_DestroyTexture(texture);
        surface = TTF_RenderUTF8_Blended(font, text.c_str(), color);
        if (!surface) {
            SDL_Log("Failed to create surface: %s", SDL_GetError());
        }
        texture = SDL_CreateTextureFromSurface(render->get(), surface);
        SDL_SetTextureBlendMode(texture, this->blendMode);
        SDL_SetTextureAlphaMod(texture, this->alpha);
        if (!texture) {
            SDL_Log("Failed to create texture: %s", SDL_GetError());
            SDL_FreeSurface(surface);
        }
    }

    void Text::flush() {
        if (texture) SDL_DestroyTexture(texture);
        surface = TTF_RenderUTF8_Blended(font, text.c_str(), color);
        if (!surface) {
            SDL_Log("Failed to create surface: %s", SDL_GetError());
        }
        texture = SDL_CreateTextureFromSurface(renderer->get(), surface);
        SDL_SetTextureBlendMode(texture, this->blendMode);
        SDL_SetTextureAlphaMod(texture, this->alpha);
        if (!texture) {
            SDL_Log("Failed to create texture: %s", SDL_GetError());
            SDL_FreeSurface(surface);
        }
    }

    void Text::draw() {
        renderer->copy(texture, nullptr, &rect);
        SDL_FreeSurface(surface);
    }
}
