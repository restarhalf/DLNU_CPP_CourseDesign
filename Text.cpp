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

    void Text::drawText(Renderer *render, TTF_Font *font, const std::string &text, SDL_Rect dst,
                             SDL_Color color) {
        if (texture) SDL_DestroyTexture(texture);
        SDL_Surface *sur = TTF_RenderUTF8_Blended(font, text.c_str(), color);
        if (!sur) {
            SDL_Log("Failed to create surface: %s", SDL_GetError());

        }

        texture = SDL_CreateTextureFromSurface(render->get(), sur);
        SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
        SDL_SetTextureAlphaMod(texture, 115);
        if (!texture) {
            SDL_Log("Failed to create texture: %s", SDL_GetError());
            SDL_FreeSurface(sur);

        }

        render->copy(texture, nullptr, &dst);


        SDL_FreeSurface(sur);

    }

    void Text::setTexture(SDL_BlendMode a) {
        SDL_SetTextureBlendMode(texture, a);
    }

    SDL_Texture * Text::getTexture() const {
        return texture;
    }
}
