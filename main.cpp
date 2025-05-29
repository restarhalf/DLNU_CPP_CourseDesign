//
//Create by Tang Team on 2025/5/26.
//
#include "Controller.h"
#include"Game.h"
#include "ServerSide.cpp"
#include "Text.h"

int main(int argc, char *args[]) {
    Game game;
    game.init("Game",800,600, 0);
    while (game.running()) {
        game.frameStart();
        game.handleEvents();
        game.update();
        game.render();
        Text text;
        game.setRenderer(text.drawText(game.getRenderer(), game.getFont(), "Hello World", {100, 100, 100, 100}, {107, 21, 21, 255}));
        SDL_RenderPresent(game.getRenderer());
        game.frameEnd();
    }
    return 0;
}