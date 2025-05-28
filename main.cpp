//
//Create by Tang Team on 2025/5/26.
//
#include"ClientSide.h"
#include "ServerSide.cpp"
int main(int argc, char* args[]) {
    Game game;
    game.init("Game", 800, 600, 0);
    while (game.running()) {
        game.handleEvents();
        game.update();
        game.render();
    }
    return 0;
}