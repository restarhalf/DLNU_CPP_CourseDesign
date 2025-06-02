//
// Create by Tang Team on 2025/5/26.
//
#include<lyt_api.h>
using namespace lyt;
int main(int argc, char *argv[])
{
    Game   game;
    bool fl=false;
    Button login;
    Button exit;
    Button fullscreen;
    TTF_Font * font= nullptr;
    game.init("Game", 1230, 540, 0);
    game.getWindow()->setIcon("asset/images/4.png");
    Image image;
    int   w = 0, h = 0, x = 0, y = 0, x1 = 0, y1 = 0;
    Text  text;
    font = TTF_OpenFont("asset/fonts/MSYH.ttf", 720);
    game.getWindow()->getSize(w, h);
    login.setButtonwithImage("asset/images/3.png", game.getRenderer(), {w / 3 - 100, h / 2 + 70, 230, 230},
                            SDL_BLENDMODE_BLEND,255);
    exit.setButtonwithImage("asset/images/2.png", game.getRenderer(), {w / 3 * 2 - 100, h / 2 + 70, 230, 230},
                            SDL_BLENDMODE_BLEND, 255);
    fullscreen.setButtonwithImage("asset/images/0.png", game.getRenderer(), {x1, y1, 100, 100},
                            SDL_BLENDMODE_BLEND, 255);
    image.setImage("asset/images/1.jpg", game.getRenderer(), {0, 0, w, h},
                            SDL_BLENDMODE_BLEND, 255);
    text.setAll(game.getRenderer(), {x, y, w / 2, h / 10}, {225, 225, 225, 225}, font, SDL_BLENDMODE_BLEND,
                "按F1切换鼠标移动或键盘移动");
    while (game.running())
    {
        game.frameStart();
        SDL_GetWindowSize(game.getWindow()->get(), &w, &h);
        image.setRect({0, 0, w, h});
        login.setButtonwithImage({w / 3 - 115, h / 2 + 70, 230, 230});
        exit.setButtonwithImage({w / 3 * 2 - 115, h / 2 + 70, 230, 230});
        fullscreen.setButtonwithImage({x1, y1, 300, 100});
        game.getRenderer()->clear();
        image.draw();
        text.draw();
        login.drawwithImage();
        exit.drawwithImage();
        fullscreen.drawwithImage();
        game.getRenderer()->present();
        SDL_Event TODO;
        while (SDL_PollEvent(&TODO))
        {
            game.handleEvent(TODO, x1, y1);
            login.handleEvent(TODO);
            exit.handleEvent(TODO);
            fullscreen.handleEvent(TODO);
            if (login.isButtonReleased())
            {
                SDL_Log("Login button clicked");
            }
            if (exit.isButtonReleased())
            {
                SDL_Log("Exit button clicked");
                TTF_CloseFont(font);
                game.clean();
            }
            if (fullscreen.isButtonReleased())
            {
                fl=!fl;
                SDL_Log("Fullscreen button clicked");
                game.getWindow()->fullscreen(fl);
            }
        }

        game.frameEnd();
    }

    return 0;
}
