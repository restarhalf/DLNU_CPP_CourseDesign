#include<lyt_api.h>
#include<lx_api.h>
#include <random>
int main(int argc, char* argv[])
{
    std::random_device rd;
    std::mt19937 gen(rd());
    lyt::Game game;
    lyt::Game loginUi;
    bool fullscreenFlag = false;
    lyt::Button login, exit, fullscreenBtn;
    TTF_Font* font = nullptr;

    // 初始化游戏窗口
    if (!game.init("Game", 1230, 540, 0)||!loginUi.init("Login", 1230, 540, 0))
    {
        SDL_Log("Failed to initialize game");
        return -1;
    }
    game.getWindow()->fullscreen(true);
    loginUi.getWindow()->fullscreen(true);
    loginUi.getWindow()->hide(false);
    game.getWindow()->setIcon("asset/images/4.png");
    loginUi.getWindow()->setIcon("asset/images/4.png");

    lyt::Image background;
    lyt::Image loginBackground;
    lyt::Text scoreText;
    int windowW = 0, windowH = 0;
    int mouseX = 0, mouseY = 0;
    int loginUiW = 0, loginUiH = 0;

    // 加载字体
    font = TTF_OpenFont("asset/fonts/MSYH.ttf", 720);
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
    loginUi.getWindow()->getSize(loginUiW, loginUiH);
    // 设置按钮和背景图片
    login.setButtonwithImage("asset/images/3.png", loginUi.getRenderer(),
        { loginUiW / 3 - 100, loginUiH / 2 + 70, 230, 230 }, SDL_BLENDMODE_BLEND, 255);
    exit.setButtonwithImage("asset/images/2.png", loginUi.getRenderer(),
        { loginUiW / 3 * 2 - 100, loginUiH / 2 + 70, 230, 230 }, SDL_BLENDMODE_BLEND, 255);
    fullscreenBtn.setButtonwithImage("asset/images/0.png", game.getRenderer(),
        { 0, 0, 100, 100 }, SDL_BLENDMODE_BLEND, 255);

    background.setImage("asset/images/1.jpg", game.getRenderer(),
        { 0, 0, windowW, windowH }, SDL_BLENDMODE_BLEND, 255);
    loginBackground.setImage("asset/images/1.jpg", loginUi.getRenderer(),
        { 0, 0, loginUiW, loginUiH }, SDL_BLENDMODE_BLEND, 255);

    // 分数管理器和分数文本 
    lx::ScoreManager scoreManager;
    SDL_Color textColor = { 255, 0, 0, 255 };
    scoreText.setAll(game.getRenderer(), { 200, 200, 400, 60 },
        textColor, font, SDL_BLENDMODE_BLEND, "Score: 0  High: 0");

    // 玩家鱼初始化
    lx::PlayerFish playerFish(game.getRenderer(), "asset/images/4.png", windowW / 2, windowH / 2, 60, 60);

    // AI鱼初始化
    std::vector<lx::AIFish> aiFishes;

    for (int i = 0; i < 10; ++i) {
        std::uniform_int_distribution<int> disX(0, windowW - 60);
        std::uniform_int_distribution<int> disY(0, windowH - 60);
        int x = disX(gen);
        int y = disY(gen);
        std::uniform_int_distribution<int> disSize(20, 60);
        int size = disSize(gen);
        aiFishes.emplace_back(game.getRenderer(), "asset/images/4.png", x, y, size, size);
    }

    // 游戏主循环
    while (game.running()) {
        game.frameStart();
        game.getWindow()->getSize(windowW, windowH);
        loginUi.getWindow()->getSize(loginUiW, loginUiH);
        background.setRect({ 0, 0, windowW, windowH });
        loginBackground.setRect({ 0, 0, loginUiW, loginUiH });

        // 按钮位置自适应窗口
        login.setButtonwithImage({ loginUiW / 3 - 115, loginUiH/ 2 + 70, 230, 230 });
        exit.setButtonwithImage({ loginUiW/ 3 * 2 - 115,loginUiH / 2 + 70, 230, 230 });
        fullscreenBtn.setButtonwithImage({ 0, 0, 300, 100 });

        SDL_Event event;
        while (SDL_PollEvent(&event)) {

            game.handleEvent(event, mouseX, mouseY);
            loginUi.handleEvent(event, mouseX, mouseY);
            login.handleEvent(event);
            exit.handleEvent(event);
            fullscreenBtn.handleEvent(event);

            playerFish.handleInput(game.getController());

            if (login.isButtonReleased())
            {
                loginUi.getWindow()->hide(true);
                game.getWindow()->setSize(loginUiW, loginUiH);
                game.getWindow()->hide(false);

                SDL_Log("Login button clicked");
            }
            if (exit.isButtonReleased()) {
                scoreManager.saveHighScore();
                if (font)
                TTF_CloseFont(font);
                game.clean();
                loginUi.clean();
                return 0;
            }
            if (fullscreenBtn.isButtonReleased()) {
                fullscreenFlag = !fullscreenFlag;
                game.getWindow()->fullscreen(fullscreenFlag);
                loginUi.getWindow()->fullscreen(fullscreenFlag);
                if (!fullscreenFlag) {
                    game.getWindow()->setSize(windowW-100, windowH-100);
                    SDL_SetWindowPosition(game.getWindow()->get(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

                }
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
                if (font)
                TTF_CloseFont(font);
                loginUi.clean();
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
            std::uniform_int_distribution<int> disX(0, windowW - 60);
            std::uniform_int_distribution<int> disY(0, windowH - 60);
            int x = disX(gen);
            int y = disY(gen);
            int playerSize = (playerFish.getRect().w + playerFish.getRect().h) / 2;
            std::uniform_int_distribution<int> disMinSize(20, playerSize * 0.8);
            std::uniform_int_distribution<int> disMaxSize(playerSize * 1.1, playerSize * 1.5);
            int minSize = disMinSize(gen);
            int maxSize = disMaxSize(gen);
            std::uniform_int_distribution<int> disSize(minSize, maxSize);
            int size = disSize(gen);
            aiFishes.emplace_back(game.getRenderer(), "asset/images/4.png", x, y, size, size);
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
        loginUi.getRenderer()->clear();
        game.getRenderer()->clear();
        loginBackground.draw();
        login.drawwithImage();
        exit.drawwithImage();
        background.draw();
        fullscreenBtn.drawwithImage();
        playerFish.render();
        scoreText.draw();
        for (auto& aiFish : aiFishes) aiFish.render();
        loginUi.getRenderer()->present();
        game.getRenderer()->present();

        game.frameEnd();
    }

    // 游戏结束保存分数并清理资源
    scoreManager.saveHighScore();
    if (font)
    TTF_CloseFont(font);
    TTF_Quit();
    game.clean();
    return 0;
}
