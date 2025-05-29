//
//Create by Tang Team on 2025/5/26.
//
#include "Controller.h"
#include"Game.h"
#include "ServerSide.cpp"
int main(int argc, char* args[]) {
    Game game;
    game.init("Game", 800, 600, 0);
    while (game.running()) {
        game.frameStart();
        game.handleEvents();
        game.update();
        game.render();
        game.frameEnd();
    }
    return 0;
}