//
// Create by Tang Team on 2025/5/26.
//
#include <bits/stdc++.h>
#include <random>
#include <ranges>

#include "Controller.h"
#include "Game.h"
#include "Image.h"
#include "ServerSide.cpp"
#include "Text.h"
using namespace lyt;

int main(int argc, char *argv[]) {
    Game game;
    game.init("Game", 800, 600, 0);
    SDL_SetWindowIcon(game.getWindow()->get(), IMG_Load("1.png"));
    Image image;
    int w = 0, h = 0, x = 0, y = 0, x1 = 0, y1 = 0;
    Text text;
    while (game.running()) {
        game.frameStart();
        game.getRenderer()->clear();
        text.setAll(game.getRenderer(), {x1, y1, 150, 30}, {0, 0, 0, 0}, game.getFont(), SDL_BLENDMODE_BLEND,
                    "按F1切换鼠标移动或键盘移动", 155);
        image.setImage("1.png", game.getRenderer(), {x, y, 200, 200}, SDL_BLENDMODE_BLEND, 155);
        text.draw();
        image.draw();
        game.getRenderer()->present();
        game.handleEvents(x, y);
        game.frameEnd();
    }

    return 0;
}
