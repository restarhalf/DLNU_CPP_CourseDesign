//
// Created by restarhalf on 2025/5/28.
//

#include "Controller.h"
namespace lyt
{
    Controller::Controller()= default;

    Controller::~Controller()= default;

    void Controller::event(SDL_Event &event, int &x, int &y)
    {
        switch (event.type)
        {
            case SDL_KEYDOWN:
                if (isKeytoMove) KeyboardPress(event, x, y);
                if (event.key.keysym.sym == SDLK_F1)
                {
                    isMousetoMove = !isMousetoMove;
                    isKeytoMove   = !isKeytoMove;
                    std::cout << "isMousetoMove:" << isMousetoMove << std::endl;
                }
                break;
            case SDL_KEYUP:
                KeyboardRelease(event, x, y);
                break;
            case SDL_MOUSEBUTTONDOWN:
                MousePress(event);
                break;
            case SDL_MOUSEBUTTONUP:
                MouseRelease(event);
                break;
            case SDL_MOUSEMOTION:
                if (isMousetoMove) MouseMove(event, x, y);
                break;
            default:
                break;
        }
    }

    void Controller::KeyboardPress(const SDL_Event &event, int &x, int &y)
    {
        switch (event.key.keysym.sym)
        {
            case SDLK_w:
                SDL_Log("w");
                y--;
                break;
            case SDLK_s:
                SDL_Log("s");
                y++;
                break;
            case SDLK_a:
                SDL_Log("a");
                x--;
                break;
            case SDLK_d:
                SDL_Log("d");
                x++;
                break;
            case SDLK_UP:
                y--;
                break;
            case SDLK_LEFT:
                x--;
                break;
            case SDLK_RIGHT:
                x++;
                break;
            case SDLK_DOWN:
                y++;
                break;
            case SDLK_SPACE:
                break;
            default:
                break;
        }
    }

    void Controller::KeyboardRelease(const SDL_Event &event, int &x, int &y)
    {
        switch (event.key.keysym.sym)
        {
            case SDLK_w:
                y--;
                break;
            case SDLK_s:
                y++;
                break;
            case SDLK_a:
                x--;
                break;
            case SDLK_d:
                x++;
                break;
            case SDLK_UP:
                y--;
                break;
            case SDLK_LEFT:
                x--;
                break;
            case SDLK_RIGHT:
                x++;
                break;
            case SDLK_DOWN:
                y++;
                break;
            case SDLK_SPACE:
                break;
            default:
                break;
        }
    }

    void Controller::MousePress(const SDL_Event &event)
    {
        switch (event.button.button)
        {
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

    void Controller::MouseRelease(const SDL_Event &event)
    {
        switch (event.button.button)
        {
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

    void Controller::MouseMove(const SDL_Event &event, int &x, int &y)
    {
        x = event.motion.x;
        y = event.motion.y;
        SDL_Log("Mouse moved to (%d, %d)", x, y);
    }
}  // namespace lyt
