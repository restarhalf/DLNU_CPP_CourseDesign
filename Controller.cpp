//
// Created by restarhalf on 2025/5/28.
//

#include "Controller.h"
void Controller::event(SDL_Event &event) {
    switch (event.type) {
            case SDL_KEYDOWN:
            KeyboardPress(event);
            break;
            case SDL_KEYUP:
            KeyboardRelease(event);
            break;
            case SDL_MOUSEBUTTONDOWN:
            MousePress(event);
            break;
            case SDL_MOUSEBUTTONUP:
            MouseRelease(event);
            break;
            case SDL_MOUSEMOTION:
            MouseMove(event);
            break;
    }
}

void Controller::KeyboardPress(SDL_Event &event) {
    switch (event.key.keysym.sym) {
        case SDLK_w:
            break;
        case SDLK_s:
            break;
        case SDLK_a:
            break;
        case SDLK_d:
            break;
        case SDLK_SPACE:
            break;
        default:
            break;
    }
}

void Controller::KeyboardRelease(SDL_Event &event) {
    switch (event.key.keysym.sym) {
        case SDLK_w:
            break;
        case SDLK_s:
            break;
        case SDLK_a:
            break;
        case SDLK_d:
            break;
        case SDLK_SPACE:
            break;
        default:
            break;
    }
}

void Controller::MousePress(SDL_Event &event) {
    switch (event.button.button) {
        case SDL_BUTTON_LEFT:
            break;
        case SDL_BUTTON_RIGHT:
            break;
        case SDL_BUTTON_MIDDLE:
            break;
        default:
            break;
    }
}

void Controller::MouseRelease(SDL_Event &event) {
    switch (event.button.button) {
        case SDL_BUTTON_LEFT:
            break;
        case SDL_BUTTON_RIGHT:
            break;
        case SDL_BUTTON_MIDDLE:
            break;
        default:
            break;
    }
}

void Controller::MouseMove(SDL_Event &event) {
};
