//
// Created by restarhalf on 2025/5/28.
//

#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_image.h>


class Controller {
public:
    Controller();
    ~Controller();
    //动作监视器
    static void event(SDL_Event &event);

    static void KeyboardPress(const SDL_Event &event);

    static void KeyboardRelease(const SDL_Event &event);

    static void MousePress(const SDL_Event &event);

    static void MouseRelease(const SDL_Event &event);

    static void MouseMove(SDL_Event &event);

};


#endif //CONTROLLER_H
