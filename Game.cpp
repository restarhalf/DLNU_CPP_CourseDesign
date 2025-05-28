//
// Created by restarhalf on 2025/5/28.
//
#include "Game.h"

#include <iostream>

#include "Controller.h"

Game::Game() {
    isRunning = false;
    renderer = nullptr;
    window = nullptr;
}

Game::~Game() {
    clean();
}

bool Game::init(const std::string& title, int width, int height, int flags) {
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        SDL_Log("Window init success");
        window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
        if(window) {
            SDL_Log("Window created");
        }
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if(renderer) {
            SDL_Log("Renderer created");
        }
        isRunning = true;
    }
    else
    {
        SDL_Log("Window init failed");
        isRunning= false;
    }
    return isRunning;
}

void Game::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            isRunning = false;
        }
        Controller::event(event);
    }
}

void Game::clean() const {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    SDL_Log("Game cleaned");
}

void Game::update() {
}

void Game::render() const {
    SDL_SetRenderDrawColor(renderer, 1000, 1000, 1000, 1000);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

bool Game::running() const{
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

