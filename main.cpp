//
//Create by Tang Team on 2025/5/26.
//
#include <random>
#include <ranges>
#include <bits/stdc++.h>
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

    // 在循环外创建图片和文本对象
    Image image;
    int w=0,h=0, x=0,y=0, x1=0,y1=0;
    std::random_device rd;
    std::random_device rd1;
    std::random_device rd2;
    std::random_device rd3;
    Text text;

    while (game.running()) {
        game.frameStart();
        game.handleEvents(x1, y1);
        // 清屏
        game.getRenderer()->clear();

        // 渲染图片

        image.drawImage("1.png", game.getRenderer(),{x,y,200,200});
        // 渲染文本
        text.drawText(game.getRenderer(), game.getFont(), "Hello World", {x1, y1, 300, 100}, {0, 0, 0, 255});
        SDL_SetTextureAlphaMod(text.getTexture(), 100);
        // 呈现渲染的内容
        game.getRenderer()->present();

        game.frameEnd();
    }

    return 0;
}
