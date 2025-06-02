#include "api.h"
//#include "Fish.h"  
#include "AIFish.h"
#include "PlayerFish.h"

#include <vector>
#include <cstdlib>
#include <ctime>

int main(int argc, char* argv[])
{
    srand((unsigned)time(nullptr));  // 初始化随机数

    lyt::Game game;
    bool fullscreenFlag = false;
    lyt::Button login;
    lyt::Button exit;
    lyt::Button fullscreenBtn;
    TTF_Font* font = nullptr;

    if (!game.init("Game", 1230, 540, 0))
    {
        SDL_Log("Failed to initialize game");
        return -1;
    }

    game.getWindow()->setIcon("asset/images/4.png");

    lyt::Image image;
    lyt::Text text;

    int windowW = 0, windowH = 0;
    int mouseX = 0, mouseY = 0;

    font = TTF_OpenFont("asset/fonts/MSYH.ttf", 72);
    if (!font)
    {
        SDL_Log("Failed to load font: %s", TTF_GetError());
        return -1;
    }

    game.getWindow()->getSize(windowW, windowH);

    login.setButtonwithImage("asset/images/3.png", game.getRenderer(),
        SDL_Rect{ windowW / 3 - 100, windowH / 2 + 70, 230, 230 },
        SDL_BLENDMODE_BLEND, 255);
    exit.setButtonwithImage("asset/images/2.png", game.getRenderer(),
        SDL_Rect{ windowW / 3 * 2 - 100, windowH / 2 + 70, 230, 230 },
        SDL_BLENDMODE_BLEND, 255);
    fullscreenBtn.setButtonwithImage("asset/images/0.png", game.getRenderer(),
        SDL_Rect{ 0, 0, 100, 100 },
        SDL_BLENDMODE_BLEND, 255);

    image.setImage("asset/images/1.jpg", game.getRenderer(), SDL_Rect{ 0, 0, windowW, windowH },
        SDL_BLENDMODE_BLEND, 255);

    text.setAll(game.getRenderer(), SDL_Rect{ 0, 0, windowW / 2, windowH / 10 },
        SDL_Color{ 225, 225, 225, 225 }, font, SDL_BLENDMODE_BLEND,
        "按F1切换鼠标移动或键盘移动");

    lx::PlayerFish playerFish(game.getRenderer()->get(), windowW / 2, windowH / 2, 60, 60);

    std::vector<lx::AIFish> aiFishes;
    for (int i = 0; i < 10; ++i)
    {
        int x = rand() % (windowW - 60);
        int y = rand() % (windowH - 60);
        int size = 20 + rand() % 40;
        aiFishes.emplace_back(game.getRenderer()->get(), x, y, size, size);
    }

    while (game.running())
    {
        game.frameStart();

        SDL_GetWindowSize(game.getWindow()->get(), &windowW, &windowH);

        image.setRect(SDL_Rect{ 0, 0, windowW, windowH });

        login.setButtonwithImage(SDL_Rect{ windowW / 3 - 115, windowH / 2 + 70, 230, 230 });
        exit.setButtonwithImage(SDL_Rect{ windowW / 3 * 2 - 115, windowH / 2 + 70, 230, 230 });
        fullscreenBtn.setButtonwithImage(SDL_Rect{ 0, 0, 300, 100 });

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            game.handleEvent(event, mouseX, mouseY);
            login.handleEvent(event);
            exit.handleEvent(event);
            fullscreenBtn.handleEvent(event);

            if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
            {
                bool pressed = (event.type == SDL_KEYDOWN);
                switch (event.key.keysym.sym)
                {
                case SDLK_w: playerFish.moveUp(pressed); break;
                case SDLK_s: playerFish.moveDown(pressed); break;
                case SDLK_a: playerFish.moveLeft(pressed); break;
                case SDLK_d: playerFish.moveRight(pressed); break;
                default: break;
                }
            }

            if (login.isButtonReleased())
            {
                SDL_Log("Login button clicked");
            }
            if (exit.isButtonReleased())
            {
                SDL_Log("Exit button clicked");
                TTF_CloseFont(font);
                game.clean();
                return 0;
            }
            if (fullscreenBtn.isButtonReleased())
            {
                fullscreenFlag = !fullscreenFlag;
                SDL_Log("Fullscreen button clicked");
                game.getWindow()->fullscreen(fullscreenFlag);
            }
        }

        playerFish.update(windowW, windowH);

        // AI鱼更新和吃鱼逻辑
        for (auto it = aiFishes.begin(); it != aiFishes.end(); )
        {
            it->update(windowW, windowH);  // AI鱼左右移动逻辑在这里实现

            // AI鱼吃玩家，玩家死亡，游戏结束
            if (it->tryEat(playerFish))
            {
                SDL_Log("玩家被比自己大的AI鱼吃掉，游戏结束");
                game.clean();
                TTF_CloseFont(font);
                return 0;
            }

            // 玩家吃AI鱼，玩家成长，AI鱼消失
            if (playerFish.tryEat(*it))
            {
                it = aiFishes.erase(it);
            }
            else
            {
                ++it;
            }
        }
        const int MAX_AI_FISH = 10;
        // 动态补充AI鱼，保持数量不变，且大小随玩家成长调整
        while ((int)aiFishes.size() < MAX_AI_FISH)
        {
            int x = rand() % (windowW - 60);
            int y = rand() % (windowH - 60);

            // 根据玩家大小调整AI鱼大小，AI鱼大小在玩家大小附近浮动，比如 +-20%
            int playerSize = (playerFish.getWidth() + playerFish.getHeight()) / 2;
            int minSize = static_cast<int>(playerSize * 0.8);
            int maxSize = static_cast<int>(playerSize * 1.2);
            if (minSize < 20) minSize = 20;  // 保证AI鱼最小尺寸
            if (maxSize < 20) maxSize = 20;

            int size = minSize + rand() % (maxSize - minSize + 1);

            aiFishes.emplace_back(game.getRenderer()->get(), x, y, size, size);
        }

        game.getRenderer()->clear();

        image.draw();
        text.draw();
        login.drawwithImage();
        exit.drawwithImage();
        fullscreenBtn.drawwithImage();

        playerFish.render();
        for (auto& aiFish : aiFishes)
        {
            aiFish.render();
        }

        game.getRenderer()->present();

        game.frameEnd();
    }

    TTF_CloseFont(font);
    game.clean();

    return 0;
}
