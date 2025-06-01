//
// Created by restarhalf on 2025/5/28.
//
#include "Game.h"

#include <utility>

#include "Controller.h"
#include "SDL_egl.h"

namespace lyt
{
    Game::Game() : window(nullptr), renderer(nullptr), isRunning(false), font(nullptr) {}

    Game::~Game() { clean(); }

    bool Game::init(std::string title, int width, int height, int flags)
    {
        if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        {
            SDL_Log("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
            isRunning = false;
            return false;
        }
        else
        {
            SDL_Log("SDL initialized");
            isRunning = true;
        }
        try
        {
            window = new Window(std::move(title), width, height);
            SDL_Log("Window created");
        }
        catch (const std::runtime_error &e)
        {
            SDL_Log("Window could not be created! SDL_Error: %s\n", e.what());
            isRunning = false;
            return false;
        }
        try
        {
            renderer = new Renderer(window, true);
            SDL_Log("Renderer created");
        }
        catch (const std::runtime_error &e)
        {
            SDL_Log("Renderer could not be created! SDL_Error: %s\n", e.what());
            if (window)
            {
                delete window;
                window = nullptr;
            }
            isRunning = false;
            return false;
        }

        isRunning = true;


        if (TTF_Init() == -1)
        {
            SDL_Log("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
            isRunning = false;
            return false;
        }
        else
        {
            SDL_Log("SDL_TTF initialized");
        }
        font = TTF_OpenFont("MSYH.ttf", 720);
        if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG && IMG_Init(IMG_INIT_JPG) != IMG_INIT_JPG)
        {
            SDL_Log("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
            isRunning = false;
            return false;
        }
        else
        {
            SDL_Log("IMG initialized");
        }
        return isRunning;
    }

    void Game::handleEvent(SDL_Event &event, int &x, int &y)
    {
        if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
        {
            isRunning = false;
        }
        controller.event(event, x, y);
    }

    void Game::clean()
    {
        delete renderer;
        delete window;
        SDL_Quit();
        IMG_Quit();
        TTF_Quit();
        SDL_Log("Game cleaned");
        exit(0);
    }

    void Game::update() const
    {
        if (renderer)
        {
            renderer->clear();
            renderer->present();
        }
    }

    void Game::render() const
    {
        if (renderer)
        {
            renderer->clear();
            renderer->present();
        }
    }

    bool Game::running() const { return isRunning; }

    void Game::frameStart() { Start = SDL_GetTicks(); }

    void Game::frameEnd()
    {
        Time = SDL_GetTicks() - Start;
        if (Time - static_cast<Uint32>(FPS) < 0)
        {
            SDL_Delay(static_cast<Uint32>(FPS) - Time);
        }
    }

    void Game::setFps(const float fps) { FPS = 1000.f / fps; }

    Renderer *Game::getRenderer() const { return renderer; }

    Window *Game::getWindow() const { return window; }

    TTF_Font *Game::getFont() const { return font; }

    void Game::setRenderer(Renderer *renderer) { this->renderer = renderer; }

    void Game::setWindow(Window *window) { this->window = window; }

    void Game::setFont(const std::string &fontPath, int fontSize) { font = TTF_OpenFont(fontPath.c_str(), fontSize); }
}  // namespace lyt
