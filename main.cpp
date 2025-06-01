//
// Create by Tang Team on 2025/5/26.
//
#include <bits/stdc++.h>
#include <random>
#include <ranges>

#include "Button.h"
#include "Game.h"
#include "Image.h"
#include "ServerSide.cpp"
#include "Text.h"
using namespace lyt;

int main(int argc, char *argv[])
{
    Game   game;
    Button login;
    Button exit;
    game.init("Game", 2460, 1080, 0);
    SDL_SetWindowIcon(game.getWindow()->get(), IMG_Load("4.png"));
    Image image;
    int   w = 0, h = 0, x = 0, y = 0, x1 = 0, y1 = 0;
    Text  text;
    while (game.running())
    {
        game.frameStart();
        game.getRenderer()->clear();
        SDL_GetWindowSize(game.getWindow()->get(), &w, &h);
        login.setButtonwithImage("3.png", game.getRenderer(), {w/3-100, h/2+70,230,230}, SDL_BLENDMODE_BLEND, 255);
        exit.setButtonwithImage("2.png", game.getRenderer(), {w/3*2-100, h/2+70,230,230}, SDL_BLENDMODE_BLEND, 255);
        text.setAll(game.getRenderer(), {x1, y1, 150, 30}, {0, 0, 0, 0}, game.getFont(), SDL_BLENDMODE_BLEND,
                    "按F1切换鼠标移动或键盘移动", 155);
        image.setImage("1.jpg", game.getRenderer(), {0,0,w,h}, SDL_BLENDMODE_BLEND, 255);
        text.draw();
        image.draw();
        login.drawwithImage();
        exit.drawwithImage();
        game.getRenderer()->present();
        SDL_Event TODO;
        while (SDL_PollEvent(&TODO))
        {
            game.handleEvent(TODO, x, y);
            login.handleEvent(TODO);
            exit.handleEvent(TODO);
            if (exit.isButtonClicked())
            {
                game.clean();
                delete &game;
                return 0;
            }
        }

        game.frameEnd();
    }

    return 0;
}
