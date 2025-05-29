//
// Created by restarhalf on 2025/5/29.
//

#include "Text.h"

Text::Text() : texture(nullptr) {
}

Text::~Text() {
    if(texture) SDL_DestroyTexture(texture);
}

SDL_Renderer *Text::drawText(SDL_Renderer *render, TTF_Font *font, const std::string &text, SDL_Rect rect,
                             SDL_Color color) {
    if(texture) SDL_DestroyTexture(texture);
    SDL_Surface *sur = TTF_RenderUTF8_Blended(font, text.c_str(), color);
    if (!sur) {
        SDL_Log("Failed to create surface: %s", SDL_GetError());
        return render;
    }

    texture = SDL_CreateTextureFromSurface(render, sur);
    if (!texture) {
        SDL_Log("Failed to create texture: %s", SDL_GetError());
        SDL_FreeSurface(sur);
        return render;
    }

    SDL_RenderCopy(render, texture, nullptr, &rect);
    
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(sur);
    return render;
}