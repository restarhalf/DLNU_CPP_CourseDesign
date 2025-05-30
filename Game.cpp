//
// Created by restarhalf on 2025/5/28.
//
#include "Game.h"
#include <iostream>
#include <utility>
#include "Controller.h"
#include "SDL_egl.h"

namespace lyt {
    Game::Game(): window(nullptr), renderer(nullptr), isRunning(false), font(nullptr) {
    }

    Game::~Game() {
        clean();
    }

    bool Game::init(std::string title, int width, int height, int flags) {
        if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
            SDL_Log("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
            isRunning = false;
            return false;
        } else {
            SDL_Log("SDL initialized");
            isRunning = true;
        }
        try {
            window = new Window(std::move(title), width, height);
            SDL_Log("Window created");
        } catch (const std::runtime_error &e) {
            SDL_Log("Window could not be created! SDL_Error: %s\n", e.what());
            isRunning = false;
            return false;
        }
        try {
            renderer = new Renderer(window, true);
            SDL_Log("Renderer created");
        } catch (const std::runtime_error &e) {
            SDL_Log("Renderer could not be created! SDL_Error: %s\n", e.what());
            if (window) {
                delete window;
                window = nullptr;
            }
            isRunning = false;
            return false;
        }

        isRunning = true;
        TTF_Init();
        font = TTF_OpenFont("MSYH.ttf", 24);
        if (font == nullptr) {
            SDL_Log("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
            isRunning = false;
            return false;
        } else {
            SDL_Log("SDL_TTF initialized");
        }
        return isRunning;
    }

    void Game::handleEvents() {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE) {
                isRunning = false;
            }
            auto controller = Controller();
            controller.event(event);
        }
    }

    void Game::clean() const {
        delete renderer;
        delete window;
        SDL_Quit();
        SDL_Log("Game cleaned");
    }

    void Game::update() {
    }

    void Game::render() const {
        if (renderer) {
            renderer->clear();
            renderer->present();
        }
    }

    bool Game::running() const {
        return isRunning;
    }

    void Game::frameStart() {
        Start = SDL_GetTicks();
    }

    void Game::frameEnd() {
        Time = SDL_GetTicks() - Start;
        if (Time < 1000 / FPS) {
            SDL_Delay(FPS - Time);
        }
    }

    void Game::setFps(const float fps) {
        FPS = 1000.f / fps;
    }

    Renderer *Game::getRenderer() const {
        return renderer;
    }

    Window *Game::getWindow() const {
        return window;
    }

    TTF_Font *Game::getFont() const {
        return font;
    }

    void Game::setRenderer(Renderer *renderer) {
        this->renderer = renderer;
    }

    void Game::setWindow(Window *window) {
        this->window = window;
    }

    void Game::setFont(Renderer *renderer, const std::string &fontPath, int fontSize) {
        font = TTF_OpenFont(fontPath.c_str(), fontSize);
    }
}
