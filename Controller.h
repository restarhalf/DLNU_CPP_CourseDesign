//
// Created by restarhalf on 2025/5/28.
//

#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <SDL.h>

namespace lyt
{
    class Controller
    {
        bool isMousetoMove{false};
        bool isKeytoMove{true};

    public:
        Controller();

        ~Controller();

        // 动作监视器
        void event(SDL_Event &event, int &x, int &y);

    private:
        void KeyboardPress(const SDL_Event &event, int &x, int &y);

        void KeyboardRelease(const SDL_Event &event, int &x, int &y);

        void MousePress(const SDL_Event &event);

        void MouseRelease(const SDL_Event &event);

        void MouseMove(const SDL_Event &event, int &x, int &y);
    };
}  // namespace lyt


#endif  // CONTROLLER_H
