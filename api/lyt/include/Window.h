//
// Created by restarhalf on 2025/5/29.
//

#ifndef WINDOW_H
#define WINDOW_H
#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
namespace lyt
{

    class Window
    {
    public:
        Window();

        Window(SDL_Window *window);

        Window(const std::string &title, int width, int height);

        ~Window();

        void handleEvents();

        SDL_Window *get() const { return window_; }
        int         width() const { return width_; }
        int         height() const { return height_; }

    private:
        SDL_Window *window_ = nullptr;
        int         width_;
        int         height_;
        SDL_Event   event_;
    };
}  // namespace lyt
#endif  // WINDOW_H