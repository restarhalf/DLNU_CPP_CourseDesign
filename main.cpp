//
//Create by Tang Team on 2025/5/26.
//
#include <bits/stdc++.h>
#include "Controller.h"
#include"Game.h"
#include "Image.h"
#include "ServerSide.cpp"
#include "Text.h"
using namespace lyt;

int main(int argc, char *argv[]) {
    Game game;
    game.init("Game", 800, 600, 0);
    game.getRenderer()->clear();
    while (game.running()) {
        //game.frameStart();
        game.handleEvents();
        //game.update();
        game.render();
        Text text;
        game.setRenderer(text.drawText(game.getRenderer(), game.getFont(), "Hello World", {100, 100, 100, 100},
                                       {107, 21, 21, 255}));
        if () {

        }
        game.getRenderer()->present();

        Image image("1.png", game.getRenderer());
        //game.frameEnd();
    }


    return 0;
}
