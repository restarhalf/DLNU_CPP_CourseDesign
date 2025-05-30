#ifndef WINDOW_H
#define WINDOW_H
#include "Window.h"
#include <stdexcept>

namespace lyt {
    Window::Window(): width_(0), height_(0), event_() {
        window_ = nullptr;
    }

    Window::Window(SDL_Window *window): width_(0), height_(0), event_() {
        window_ = window;
    }

    Window::Window(std::string title, int width, int height)
        : width_(width), height_(height), event_() {
        window_ = SDL_CreateWindow(title.c_str(),
                                   SDL_WINDOWPOS_CENTERED,
                                   SDL_WINDOWPOS_CENTERED,
                                   width,
                                   height,
                                   SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI);

        if (!window_) {
            throw std::runtime_error(SDL_GetError());
        }
    }

    Window::~Window() {
        if (window_) {
            SDL_DestroyWindow(window_);
        }
    }

    void Window::handleEvents() {
        while (SDL_PollEvent(&event_)) {
            if (event_.type == SDL_QUIT) {
                // 需要后续在Game类中处理退出逻辑
            }
            if (event_.type == SDL_WINDOWEVENT &&
                event_.window.event == SDL_WINDOWEVENT_RESIZED) {
                width_ = event_.window.data1;
                height_ = event_.window.data2;
            }
        }
    }
}

#endif //WINDOW_H
