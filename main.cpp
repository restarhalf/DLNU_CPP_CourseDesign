/*
 * 大鱼吃小鱼游戏主程序
 * 功能：
 * 1. 实现游戏登录界面和主游戏界面
 * 2. 玩家控制鱼与AI鱼的交互
 * 3. 分数系统和全屏显示功能
 * 4. 碰撞检测和游戏结束判定
 */
#include <lx_api.h>
#include <lyt_api.h>
#include <random>

int main(int argc, char* argv[])
{
    // 随机数生成器初始化
    std::random_device rd;
    std::mt19937       gen(rd());

    // 创建游戏窗口和登录窗口对象
    lyt::Game   game;
    lyt::Game   loginUi;
    bool        fullscreenFlag = false;
    lyt::Button login, exit, fullscreenBtn;  // 创建按钮对象：登录、退出、全屏
    TTF_Font*   font = nullptr;

    // 初始化游戏窗口和登录窗口，设置分辨率和flags
    if (!game.init("Game", 1230, 540, 0) || !loginUi.init("Login", 1230, 540, 0))
    {
        SDL_Log("Failed to initialize game");
        return -1;
    }

    // 设置初始全屏状态和窗口图标
    game.getWindow()->fullscreen(true);
    loginUi.getWindow()->fullscreen(true);
    loginUi.getWindow()->hide(false);
    game.getWindow()->setIcon("asset/images/4.png");
    loginUi.getWindow()->setIcon("asset/images/4.png");

    // 创建背景图像对象
    lyt::Image background;
    lyt::Image loginBackground;
    lyt::Text  scoreText;
    int        windowW = 0, windowH = 0;  // 游戏窗口尺寸
    int        mouseX = 0, mouseY = 0;  // 鼠标坐标
    int        loginUiW = 0, loginUiH = 0;  // 登录窗口尺寸

    // 加载字体
    font = TTF_OpenFont("asset/fonts/MSYH.ttf", 20);
    if (!font)
    {
        SDL_Log("Failed to load font: %s", TTF_GetError());
        // 尝试备用字体
        font = TTF_OpenFont("arial.ttf", 20);
        if (!font)
        {
            SDL_Log("Failed to load fallback font: %s", TTF_GetError());
            return -1;
        }
    }

    game.getWindow()->getSize(windowW, windowH);
    loginUi.getWindow()->getSize(loginUiW, loginUiH);
    // 设置按钮和背景图片
    login.setButtonwithImage("asset/images/3.png", loginUi.getRenderer(),
                             {loginUiW / 3 - 100, loginUiH / 2 + 70, 230, 230}, SDL_BLENDMODE_BLEND, 255);
    exit.setButtonwithImage("asset/images/2.png", loginUi.getRenderer(),
                            {loginUiW / 3 * 2 - 100, loginUiH / 2 + 70, 230, 230}, SDL_BLENDMODE_BLEND, 255);
    fullscreenBtn.setButtonwithImage("asset/images/0.png", game.getRenderer(), {0, 0, 100, 100}, SDL_BLENDMODE_BLEND,
                                     255);

    background.setImage("asset/images/background.png", game.getRenderer(), {0, 0, windowW, windowH},
                        SDL_BLENDMODE_BLEND, 255);
    loginBackground.setImage("asset/images/background.png", loginUi.getRenderer(), {0, 0, loginUiW, loginUiH},
                             SDL_BLENDMODE_BLEND, 255);

    // 分数管理器和分数文本
    lx::ScoreManager scoreManager;
    SDL_Color        textColor = {255, 0, 0, 255};
    scoreText.setAll(game.getRenderer(), {200, 200, 400, 60}, textColor, font, SDL_BLENDMODE_BLEND,
                     "Score: 0  High: 0");

    // 玩家鱼初始化
    lx::PlayerFish playerFish(game.getRenderer(), "asset/images/fish8_left_0.png", windowW / 2, windowH / 2, 120, 60);

    // AI鱼初始化
    std::vector<lx::AIFish> aiFishes;

    for (int i = 0; i < 10; ++i)
    {
        std::uniform_int_distribution<int> disSize(20, 60);
        int                                size = disSize(gen);  // 根据随机大小设置生成地位置坐标

        // 随机选择左侧或右侧边缘
        int side = rand() % 2 == 0 ? 0 : 1;
        int x    = 0;
        if (side == 1)
        {
            x = windowW - size;  // 右侧边缘
        }

        // 随机y坐标
        std::uniform_int_distribution<int> disY(0, windowH - size);
        int                                y = disY(gen);
        if (side == 0)
            aiFishes.emplace_back(game.getRenderer(), "asset/images/player_1_right_0.png", x, y, size, size);
        else
            aiFishes.emplace_back(game.getRenderer(), "asset/images/player_1_left_0.png", x, y, size, size);
    }
    // 暂停状态变量,初始就是静止状态（游戏未开始前）
    bool paused = true;
    // 游戏主循环
    while (game.running())
    {
        // 开始新的帧
        game.frameStart();

        // 获取并更新窗口尺寸
        game.getWindow()->getSize(windowW, windowH);
        loginUi.getWindow()->getSize(loginUiW, loginUiH);
        background.setRect({0, 0, windowW, windowH});
        loginBackground.setRect({0, 0, loginUiW, loginUiH});

        // 按钮位置自适应窗口
        login.setButtonwithImage({loginUiW / 3 - 115, loginUiH / 2 + 70, 230, 230});
        exit.setButtonwithImage({loginUiW / 3 * 2 - 115, loginUiH / 2 + 70, 230, 230});
        fullscreenBtn.setButtonwithImage({0, 0, 300, 100});

        // 事件处理
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            game.handleEvent(event, mouseX, mouseY);
            loginUi.handleEvent(event, mouseX, mouseY);
            login.handleEvent(event);
            exit.handleEvent(event);
            fullscreenBtn.handleEvent(event);


            // 检测暂停键（p键）
            if (event.type == SDL_KEYDOWN)  // 还需加上点击开始/继续图标的条件语句！！！！！
            {
                if (event.key.keysym.sym == SDLK_p)
                {
                    paused = !paused;  // 暂停状态转化
                }
            }
            if (!paused)  // 暂停状态变化，若未暂停，更新移动
            {
                // 处理玩家输入
                playerFish.handleInput(game.getController());
                //playerFish.update(windowW, windowH);
            }

            if (login.isButtonReleased())
            {
                loginUi.getWindow()->hide(true);
                game.getWindow()->setSize(loginUiW, loginUiH);
                game.getWindow()->hide(false);
                paused = false;
                SDL_Log("Login button clicked");
            }
            if (exit.isButtonReleased())
            {
                scoreManager.saveHighScore();
                if (font) TTF_CloseFont(font);
                game.clean();
                loginUi.clean();
                return 0;
            }
            if (fullscreenBtn.isButtonReleased())
            {
                fullscreenFlag = !fullscreenFlag;
                game.getWindow()->fullscreen(fullscreenFlag);
                loginUi.getWindow()->fullscreen(fullscreenFlag);
                if (!fullscreenFlag)
                {
                    game.getWindow()->setSize(windowW - 100, windowH - 100);
                    SDL_SetWindowPosition(game.getWindow()->get(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
                }
            }
        }

        if (!paused)
        {
            // 玩家鱼和AI鱼的更新逻辑
            playerFish.update(windowW, windowH);

            // AI鱼更新与碰撞检测循环
            for (auto it = aiFishes.begin(); it != aiFishes.end();)
            {
                it->update(windowW, windowH);  // 位置更新

                if (!playerFish.isAlive())
                {
                    SDL_Log("玩家死亡，游戏结束");
                    scoreManager.saveHighScore();
                    if (font) TTF_CloseFont(font);
                    loginUi.clean();
                    game.clean();
                    return 0;
                }

                playerFish.tryEat(*it, scoreManager);  // 循环判断

                if (!it->isAlive())
                    it = aiFishes.erase(it);
                else
                    ++it;
            }
        }


        // 维持AI鱼的数量，确保始终有足够的AI鱼在场
        constexpr int MAX_AI_FISH = 10;
        while (static_cast<int>(aiFishes.size()) < MAX_AI_FISH)
        {
            // 先随机生成体积
            int                                playerSize = (playerFish.getRect().w + playerFish.getRect().h) / 2;
            std::uniform_int_distribution<int> disMinSize(20, static_cast<int>(playerSize * 0.8));
            std::uniform_int_distribution<int> disMaxSize(static_cast<int>(playerSize * 1.1),
                                                          static_cast<int>(playerSize * 1.5));
            int                                minSize = disMinSize(gen);
            int                                maxSize = disMaxSize(gen);
            // 确保minSize<=maxSize
            if (minSize > maxSize)
            {
                std::swap(minSize, maxSize);
            }
            std::uniform_int_distribution<int> disSize(minSize, maxSize);
            int                                size = disSize(gen);

            // 随机选择左侧或右侧边缘
            int side = rand() % 2 == 0 ? 0 : 1;
            int x    = 0;
            if (side == 1)
            {
                x = windowW - size;  // 右侧边缘
            }

            // 随机y坐标
            std::uniform_int_distribution<int> disY(0, windowH - size);
            int                                y = disY(gen);
            y                                    = disY(gen);

            // 创建AI鱼
            if (side == 0)
                aiFishes.emplace_back(game.getRenderer(), "asset/images/player_1_right_0.png", x, y, size, size);
            else
                aiFishes.emplace_back(game.getRenderer(), "asset/images/player_1_left_0.png", x, y, size, size);
            // 设置方向：左侧的鱼向右游，右侧的鱼向左游
            int dir = (side == 0) ? 1 : -1;
            aiFishes.back().setDirection(dir);
        }

        // 更新分数显示

        std::string scoreStr = "Score: " + std::to_string(scoreManager.getScore()) +
                               "  High: " + std::to_string(scoreManager.getHighScore());
        scoreText.setAll(game.getRenderer(), {10, 10, 400, 60}, textColor, font, SDL_BLENDMODE_BLEND, scoreStr);

        // 渲染游戏画面
        loginUi.getRenderer()->clear();
        game.getRenderer()->clear();
        // 渲染登录界面元素
        loginBackground.draw();
        login.drawwithImage();
        exit.drawwithImage();
        // 渲染游戏界面元素
        background.draw();
        fullscreenBtn.drawwithImage();
        playerFish.render();
        scoreText.draw();
        for (auto& aiFish: aiFishes) aiFish.render();
        // 显示渲染结果
        loginUi.getRenderer()->present();
        game.getRenderer()->present();


        // 结束当前帧
        game.frameEnd();
    }

    // 游戏结束处理：保存分数和清理资源
    scoreManager.saveHighScore();
    if (font) TTF_CloseFont(font);
    TTF_Quit();
    game.clean();
    return 0;
}
