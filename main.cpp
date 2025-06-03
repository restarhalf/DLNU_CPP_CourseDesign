#include "api.h"
#include "AIFish.h"
#include "PlayerFish.h"
#include "ScoreManager.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>

int main(int argc, char* argv[])
{
    srand((unsigned)time(nullptr));

    lyt::Game game;
    bool fullscreenFlag = false;
    lyt::Button login, exit, fullscreenBtn;
    TTF_Font* font = nullptr;

    // 初始化游戏窗口
    if (!game.init("Game", 1230, 540, 0)) {
        SDL_Log("Failed to initialize game");
        return -1;
    }

    // 初始化SDL_ttf
    if (TTF_Init() == -1) {
        SDL_Log("SDL_ttf could not initialize: %s", TTF_GetError());
        return -1;
    }

    game.getWindow()->setIcon("asset/images/4.png");

    lyt::Image background;
    lyt::Text scoreText;
    int windowW = 0, windowH = 0;
    int mouseX = 0, mouseY = 0;

    // 加载字体
    font = TTF_OpenFont("asset/fonts/MSYH.ttf", 20);
    if (!font) {
        SDL_Log("Failed to load font: %s", TTF_GetError());
        // 尝试备用字体
        font = TTF_OpenFont("arial.ttf", 20);
        if (!font) {
            SDL_Log("Failed to load fallback font: %s", TTF_GetError());
            return -1;
        }
    }

    game.getWindow()->getSize(windowW, windowH);

    // 设置按钮和背景图片
    login.setButtonwithImage("asset/images/3.png", game.getRenderer(),
        { windowW / 3 - 100, windowH / 2 + 70, 230, 230 }, SDL_BLENDMODE_BLEND, 255);
    exit.setButtonwithImage("asset/images/2.png", game.getRenderer(),
        { windowW / 3 * 2 - 100, windowH / 2 + 70, 230, 230 }, SDL_BLENDMODE_BLEND, 255);
    fullscreenBtn.setButtonwithImage("asset/images/0.png", game.getRenderer(),
        { 0, 0, 100, 100 }, SDL_BLENDMODE_BLEND, 255);

    background.setImage("asset/images/1.jpg", game.getRenderer(),
        { 0, 0, windowW, windowH }, SDL_BLENDMODE_BLEND, 255);

    // 分数管理器和分数文本 
    lx::ScoreManager scoreManager;
    SDL_Color textColor = { 255, 0, 0, 255 };
    scoreText.setAll(game.getRenderer(), { 200, 200, 400, 60 },
        textColor, font, SDL_BLENDMODE_BLEND, "Score: 0  High: 0");

    // 玩家鱼初始化
    lx::PlayerFish playerFish(game.getRenderer(), "asset/images/player.jpg", windowW / 2, windowH / 2, 60, 60);

    // AI鱼初始化
    std::vector<lx::AIFish> aiFishes;
    for (int i = 0; i < 10; ++i) {
        int x = rand() % (windowW - 60);
        int y = rand() % (windowH - 60);
        int size = 20 + rand() % 40;
        aiFishes.emplace_back(game.getRenderer(), "asset/images/ai.jpg", x, y, size, size);
    }

    // 游戏主循环
    while (game.running()) {
        game.frameStart();
        SDL_GetWindowSize(game.getWindow()->get(), &windowW, &windowH);
        background.setRect({ 0, 0, windowW, windowH });

        // 按钮位置自适应窗口
        login.setButtonwithImage({ windowW / 3 - 115, windowH / 2 + 70, 230, 230 });
        exit.setButtonwithImage({ windowW / 3 * 2 - 115, windowH / 2 + 70, 230, 230 });
        fullscreenBtn.setButtonwithImage({ 0, 0, 300, 100 });

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            game.handleEvent(event, mouseX, mouseY);
            login.handleEvent(event);
            exit.handleEvent(event);
            fullscreenBtn.handleEvent(event);

            playerFish.handleInput(game.getController());

            if (login.isButtonReleased()) SDL_Log("Login button clicked");
            if (exit.isButtonReleased()) {
                scoreManager.saveHighScore();
                TTF_CloseFont(font);
                TTF_Quit();
                game.clean();
                return 0;
            }
            if (fullscreenBtn.isButtonReleased()) {
                fullscreenFlag = !fullscreenFlag;
                game.getWindow()->fullscreen(fullscreenFlag);
            }
        }

        // 玩家鱼更新
        playerFish.update(windowW, windowH);

        // AI鱼更新与碰撞检测
        for (auto it = aiFishes.begin(); it != aiFishes.end(); ) {
            it->update(windowW, windowH);

            if (!playerFish.isAlive()) {
                SDL_Log("玩家死亡，游戏结束");
                scoreManager.saveHighScore();
                TTF_CloseFont(font);
                TTF_Quit();
                game.clean();
                return 0;
            }

            if (playerFish.tryEat(*it, scoreManager)) {
                scoreManager.add(it->getScoreValue());
            }

            if (!it->isAlive()) it = aiFishes.erase(it);
            else ++it;
        }

        // 保持AI鱼数量
        const int MAX_AI_FISH = 10;
        while ((int)aiFishes.size() < MAX_AI_FISH) {
            int x = rand() % (windowW - 60);
            int y = rand() % (windowH - 60);
            int playerSize = (playerFish.getRect().w + playerFish.getRect().h) / 2;
            int minSize = static_cast<int>(playerSize * 0.8);
            int maxSize = static_cast<int>(playerSize * 1.2);
            int size = minSize + rand() % (maxSize - minSize + 1);
            aiFishes.emplace_back(game.getRenderer(), "asset/images/ai.jpg", x, y, size, size);
        }

        // 更新分数显示 - 使用更可靠的文本更新方式
        std::string scoreStr = "Score: " + std::to_string(scoreManager.getScore()) +
            "  High: " + std::to_string(scoreManager.getHighScore());

        // 确保每次循环都重新创建文本纹理
        scoreText.setText(scoreStr);
        scoreText.setColor(textColor);
        scoreText.setRect({ 10, 10, 400, 60 });
        scoreText.setFont(font);
        scoreText.flush();

        // 渲染所有元素
        game.getRenderer()->clear();

        background.draw();
       
        login.drawwithImage();
        exit.drawwithImage();
        fullscreenBtn.drawwithImage();
        playerFish.render();
        scoreText.draw();
        for (auto& aiFish : aiFishes) aiFish.render();

        game.getRenderer()->present();
        game.frameEnd();
    }

    // 游戏结束保存分数并清理资源
    scoreManager.saveHighScore();
    TTF_CloseFont(font);
    TTF_Quit();
    game.clean();
    return 0;
}
