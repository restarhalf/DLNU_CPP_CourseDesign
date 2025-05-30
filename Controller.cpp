//
// Created by restarhalf on 2025/5/28.
//

#include "Controller.h"

#include "Game.h"

namespace lyt {
    Controller::Controller() {
    }

    Controller::~Controller() {
    }

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
            default:
                break;
        }
    }

    void Controller::KeyboardPress(const SDL_Event &event) {
        switch (event.key.keysym.sym) {
            case SDLK_w:
                break;
            case SDLK_s:
                break;
            case SDLK_a:
                break;
            case SDLK_d:
                break;
            case SDLK_UP:
                break;
            case SDLK_LEFT:
                break;
            case SDLK_RIGHT:
                break;
            case SDLK_DOWN:
                break;
            case SDLK_SPACE:
                break;
            default:
                break;
        }
    }

    void Controller::KeyboardRelease(const SDL_Event &event) {
        switch (event.key.keysym.sym) {
            case SDLK_w:
                break;
            case SDLK_s:
                break;
            case SDLK_a:
                break;
            case SDLK_d:
                break;
            case SDLK_UP:
                break;
            case SDLK_LEFT:
                break;
            case SDLK_RIGHT:
                break;
            case SDLK_DOWN:
                break;
            case SDLK_SPACE:
                break;
            default:
                break;
        }
    }

    void Controller::MousePress(const SDL_Event &event) {
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

    void Controller::MouseRelease(const SDL_Event &event) {
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

    void Controller::MouseMove(const SDL_Event &event) {
        auto mouseX = event.motion.x;
        auto mouseY = event.motion.y;
        //fish->setPosition(mouseX, mouseY);
    }
}
