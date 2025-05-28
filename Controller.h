//
// Created by restarhalf on 2025/5/28.
//

#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <SDL.h>


class Controller {

    Controller();

    ~Controller();
public:
    //动作监视器
    static void event(SDL_Event &event);

    static void KeyboardPress(SDL_Event &event);

    static void KeyboardRelease(SDL_Event &event);

    static void MousePress(SDL_Event &event);

    static void MouseRelease(SDL_Event &event);

    static void MouseMove(SDL_Event &event);
};



#endif //CONTROLLER_H
