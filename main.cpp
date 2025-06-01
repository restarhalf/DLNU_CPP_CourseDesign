//
// Create by Tang Team on 2025/5/26.
//
#include<lyt_api.h>
using namespace lyt;
int main(int argc, char *argv[])
{
    Game   game;
    Button login;
    Button exit;
    TTF_Font * font= nullptr;
    game.init("Game", 246, 108, 0);
    SDL_SetWindowIcon(game.getWindow()->get(), IMG_Load("asset/images/4.png"));
    Image image;
    int   w = 0, h = 0, x = 0, y = 0, x1 = 0, y1 = 0;
    Text  text;
    font = TTF_OpenFont("asset/fonts/MSYH.ttf", 720);
    SDL_GetWindowSize(game.getWindow()->get(), &w, &h);
    login.setButtonwithImage("asset/images/3.png", game.getRenderer(), {w / 3 - 100, h / 2 + 70, 230, 230}, SDL_BLENDMODE_BLEND,
                             255);
    exit.setButtonwithImage("asset/images/2.png", game.getRenderer(), {w / 3 * 2 - 100, h / 2 + 70, 230, 230},
                            SDL_BLENDMODE_BLEND, 255);
    image.setImage("asset/images/1.jpg", game.getRenderer(), {0, 0, w, h}, SDL_BLENDMODE_BLEND, 255);
    text.setAll(game.getRenderer(), {x1, y1, w/500, h/100}, {0, 0, 0, 0}, font, SDL_BLENDMODE_BLEND,
                "按F1切换鼠标移动或键盘移动", 255);
    while (game.running())
    {
        game.frameStart();
        SDL_GetWindowSize(game.getWindow()->get(), &w, &h);
        image.setRect({0, 0, w, h});
        login.setButton({w / 3 - 100, h / 2 + 70, 230, 230}, {0, 0, 0, 255});
        exit.setButton({w / 3 * 2 - 100, h / 2 + 70, 230, 230}, {0, 0, 0, 255});
        game.getRenderer()->clear();
        image.draw();
        text.draw();
        login.drawwithImage();
        exit.drawwithImage();
        game.getRenderer()->present();
        SDL_Event TODO;
        while (SDL_PollEvent(&TODO))
        {
            game.handleEvent(TODO, x1, y1);
            login.handleEvent(TODO);
            exit.handleEvent(TODO);
            if (login.isButtonClicked())
            {
                SDL_Log("Login button clicked");
            }
            if (exit.isButtonReleased())
            {
                SDL_Log("Exit button clicked");
                game.clean();
            }
        }

        game.frameEnd();
    }

    return 0;
}
