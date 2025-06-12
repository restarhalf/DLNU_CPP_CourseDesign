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

// 自适应函数
// 该Lambda函数用于根据窗口尺寸和比例参数计算出一个SDL_Rect矩形，常用于UI元素的自适应布局
// 参数说明：
//   windowW, windowH: 当前窗口的宽度和高度
//   widthRatio, heightRatio: 矩形宽度和高度相对于窗口的比例（0~1之间的小数）
//   xRatio, yRatio: 矩形中心点（x）和左上角（y）相对于窗口的比例（xRatio默认0.5表示水平居中，yRatio默认0.02表示顶部偏移）
// 返回值：
//   SDL_Rect结构体，表示计算得到的矩形区域
inline auto computeRect = [](int windowW, int windowH, float widthRatio, float heightRatio, float xRatio = 0.5f,
                             float yRatio = 0.02f) -> SDL_Rect
{
    // 计算矩形的宽度和高度
    int width  = static_cast<int>(static_cast<float>(windowW) * widthRatio);
    int height = static_cast<int>(static_cast<float>(windowH) * heightRatio);
    // 计算矩形左上角x坐标，使其中心点位于xRatio指定的位置
    int x = static_cast<int>(static_cast<float>(windowW) * xRatio - static_cast<float>(width) / 2);  // xRatio表示中心点的相对位置，默认0.5居中
    // 计算矩形左上角y坐标
    int y = static_cast<int>(static_cast<float>(windowH) * yRatio);
    // 返回SDL_Rect结构体
    return {x, y, width, height};
};



int main(int argc, char* argv[])
{
    // 随机数生成器初始化
    std::random_device rd;
    std::mt19937       gen(rd());
    bool isLogin=false;
    // 创建游戏窗口和登录窗口对象
    lyt::Game   game;
    lyt::Game   loginUi;
    bool        fullscreenFlag = false;
    lyt::Button login, exit, fullscreenBtn,pauseButton,restart,gameExit;  // 创建按钮对象：登录、退出、全屏
    TTF_Font*   font = nullptr;

    // 初始化游戏窗口和登录窗口，设置分辨率和flags
    if (!game.init("Game", 2460, 1080, 0) || !loginUi.init("Login", 2460, 1080, 0))
    {
        SDL_Log("Failed to initialize game");
        return -1;
    }

    // 设置初始全屏状态和窗口图标
    game.getWindow()->fullscreen(true);
    loginUi.getWindow()->fullscreen(true);
    loginUi.getWindow()->hide(false);
    game.getWindow()->setIcon("res/app_icon.ico");
    loginUi.getWindow()->setIcon("res/app_icon.ico");

    // 创建背景图像对象
    lyt::Image background;
    lyt::Image loginBackground;
    lyt::Image scoreBoard;  // 计分板背景
    lyt::Text  scoreText;
    lyt::Text  loginText;
    lyt::Image gameOverImage;
    int        windowW = 0, windowH = 0;  // 游戏窗口尺寸
    int        mouseX = 0, mouseY = 0;  // 鼠标坐标
    int        loginUiW = 0, loginUiH = 0;  // 登录窗口尺寸


    // 加载字体
    font = TTF_OpenFont("asset/fonts/AaLongyan_font.ttf", 1080);
    if (!font)
    {
        SDL_Log("Failed to load font: %s", TTF_GetError());
        // 尝试备用字体
        font = TTF_OpenFont("arial.ttf", 1080);
        if (!font)
        {
            SDL_Log("Failed to load fallback font: %s", TTF_GetError());
            return -1;
        }
    }

    game.getWindow()->getSize(windowW, windowH);
    loginUi.getWindow()->getSize(loginUiW, loginUiH);

    // 设置按钮和背景图片
    login.setButtonwithImage("asset/images/start.png", loginUi.getRenderer(),
                             {loginUiW / 3 - 100, loginUiH / 2 + 70, 206, 70}, SDL_BLENDMODE_BLEND, 255);
    exit.setButtonwithImage("asset/images/exit.png", loginUi.getRenderer(),
                            {loginUiW / 3 * 2 - 100, loginUiH / 2 + 70, 206, 70}, SDL_BLENDMODE_BLEND, 255);
    restart.setButtonwithImage("asset/images/restart.png", game.getRenderer(),{windowW/8*3-102, windowH/8*6+150, 205, 33}, SDL_BLENDMODE_BLEND, 255);
    gameExit.setButtonwithImage("asset/images/restart.png", game.getRenderer(),{windowW/8*5-53, windowH/8*6+150, 106, 33}, SDL_BLENDMODE_BLEND, 255);
    fullscreenBtn.setButtonwithImage("asset/images/restart.png", game.getRenderer(), {0, 0, 100, 100}, SDL_BLENDMODE_BLEND,
                                     255);
    pauseButton.setButtonwithImage("asset/images/pause.png", game.getRenderer(),
                            {static_cast<int>(windowW * 0.884), 0, static_cast<int>(windowW * 0.116), static_cast<int>(windowW * 0.116)}, SDL_BLENDMODE_BLEND, 255);
    background.setImage("asset/images/background.png", game.getRenderer(), {0, 0, windowW, windowH},
                        SDL_BLENDMODE_BLEND, 255);
    loginBackground.setImage("asset/images/loginbackground.png", loginUi.getRenderer(), {0, 0, loginUiW, loginUiH},
                             SDL_BLENDMODE_BLEND, 255);
    gameOverImage.setImage("asset/images/gameover.png", game.getRenderer(), {windowW/4, windowH/2, static_cast<int>(windowW*0.5), static_cast<int>(windowH*0.5)},
                             SDL_BLENDMODE_BLEND, 255);
    // 计分板背景，用固定高度比例，宽度铺满
    SDL_Rect scoreBoardRect = {0, 0, windowW, static_cast<int>(windowW*0.07)};
    scoreBoard.setImage("asset/images/bar.png", game.getRenderer(), scoreBoardRect, SDL_BLENDMODE_BLEND, 255);

    // 分数管理器和分数文本
    lx::ScoreManager scoreManager;
    SDL_Color        textColor = {255, 255, 255, 255};

SDL_Rect    scoreRect = computeRect(windowW, windowH, 0.25f, 0.07f, 0.5f, 0.02f);
    std::string scoreStr = "Score: " + std::to_string(scoreManager.getScore()) +
                           "  High: " + std::to_string(scoreManager.getHighScore());

    scoreText.setAll(game.getRenderer(), scoreRect, textColor, font, SDL_BLENDMODE_BLEND, scoreStr);

    // 登录界面文本区域，宽占登录窗口宽度的70%，高占20%，距离顶部50%，水平居中
    SDL_Rect loginTextRect = computeRect(loginUiW, loginUiH, 0.7f, 0.2f, 0.5f, 0.2f);
    loginText.setAll(loginUi.getRenderer(), loginTextRect, {30, 144, 255, 255},font, SDL_BLENDMODE_BLEND, "FISH EAT FISH");
    //loginText.setAll(loginUi.getRenderer(), loginTextRect, textColor, font, SDL_BLENDMODE_BLEND, "1111111111111111");

    // 玩家鱼初始化
    lx::PlayerFish playerFish(game.getRenderer(), "asset/images/fish8_left_0.png", windowW / 4, windowH / 2, 60, 30);

    std::vector<lx::FishType> fishTypes = {
            // 不同范围对应纹理
            {20,
             40,
             {"asset/images/fish0_left_0.png", "asset/images/fish1_left_0.png", "asset/images/fish2_left_0.png"}},
            {41,
             80,
             {"asset/images/fish2_left_0.png", "asset/images/fish3_left_0.png", "asset/images/fish4_left_0.png",
              "asset/images/fish5_left_0.png"}},
            {81,
             120,
             {"asset/images/fish3_left_0.png", "asset/images/fish4_left_0.png", "asset/images/fish5_left_0.png",
              "asset/images/fish9_left_0.png"}},
            {121,
             500,  // 满足体积最大值
             {"asset/images/fish6_left_0.png", "asset/images/fish7_left_0.png", "asset/images/fish8_left_0.png"}}

    };
    bool paused = true;

    // AI鱼初始化
    std::vector<lx::AIFish> aiFishes;
    resartLabel:
    for (int i = 0; i < 10; ++i)
    {
        // 获取玩家鱼体积（例如取宽高的平均值）
        int playerSize = (playerFish.getRect().w + playerFish.getRect().h) / 2;

        // 初始化或补充AI鱼时传入玩家体积
        aiFishes.push_back(
                lx::AIFish::createRandomFish(game.getRenderer(), fishTypes, windowW, windowH, gen, playerSize));
    }
    // 暂停状态变量,初始就是静止状态（游戏未开始前）

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
        scoreBoard.setRect({0, 0, windowW, static_cast<int>(windowW*0.07)});  // 更新计分板尺寸
        gameOverImage.setRect({windowW/4, windowH/4, static_cast<int>(windowW*0.5), static_cast<int>(windowH*0.5)});


        // 按钮位置自适应窗口
        login.setButtonwithImage({loginUiW / 2 - 103, loginUiH / 2 + 100, 206, 70});
        exit.setButtonwithImage({loginUiW / 2-103, loginUiH / 2 + 300, 206, 70});
        fullscreenBtn.setButtonwithImage({0, 0, 300, 100});
        pauseButton.setButtonwithImage({static_cast<int>(windowW * 0.93), 0, static_cast<int>(windowW * 0.07), static_cast<int>(windowW * 0.07)});
        restart.setButtonwithImage({windowW/8*3-43, windowH/8*5, 86, 75});
        gameExit.setButtonwithImage({windowW/8*5-43, windowH/8*5, 86, 75});
        // 使用余弦函数的平滑渐变
        if (!isLogin)
        {
            Uint32 ticks  = SDL_GetTicks();
        double  colorT = (ticks % 2000) / 2000.0 * 2.0 * M_PI;  // 0到2π

        // 蓝紫渐变（R: 较小变化，G: 中值变化，B: 大幅变化）
        auto  r = static_cast<Uint8>(100 + 30 * cos(colorT));  // 红: 100~130
        auto  g = static_cast<Uint8>(50 + 50 * cos(colorT + M_PI / 2.0f));  // 绿: 0~100（紫色需要较少绿色）
        auto  b = static_cast<Uint8>(150 + 50 * cos(colorT));  // 蓝: 50~250

        SDL_Color fadeColor = {r, g, b, 255};
        loginText.setColor(fadeColor);
        }


        // 事件处理
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (!isLogin)
            {
                loginUi.handleEvent(event, mouseX, mouseY);
                login.handleEvent(event);
                exit.handleEvent(event);
                if (login.isButtonReleased())  // 登录按钮
                {
                    loginUi.getWindow()->hide(true);
                    game.getWindow()->setSize(loginUiW, loginUiH);
                    game.getWindow()->hide(false);
                    isLogin = true;
                    paused = false;
                    SDL_Log("Login button clicked");
                }
                if (exit.isButtonReleased())  // 退出
                {
                    scoreManager.saveHighScore();
                    TTF_CloseFont(font);
                    game.clean();
                    loginUi.clean();
                    return 0;
                }
            }
            else if (playerFish.isAlive())// 游戏界面事件处理
            {
                game.handleEvent(event, mouseX, mouseY);

            pauseButton.handleEvent(event);
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
                // playerFish.update(windowW, windowH);
            }
            if (pauseButton.isButtonReleased())
            {
                paused = !paused;
            }
            if (fullscreenBtn.isButtonReleased())  // 全屏
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
            if (!playerFish.isAlive())
            {
                restart.handleEvent(event);
                gameExit.handleEvent(event);
                if (restart.isButtonReleased())
                {
                    paused = false;
                    playerFish.reset(windowW / 4, windowH / 2,game.getController());
                    aiFishes.clear();
                    scoreManager.reset();
                    goto resartLabel;
                }
                if (gameExit.isButtonReleased())
                {
                    scoreManager.saveHighScore();
                    TTF_CloseFont(font);
                    game.clean();
                    loginUi.clean();
                    return 0;
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
                    // SDL_Log("玩家死亡，游戏结束");
                    scoreManager.saveHighScore();
                    paused = true;
                    SDL_SetRenderDrawBlendMode(game.getRenderer()->get()
                        , SDL_BLENDMODE_BLEND);
                    SDL_SetRenderDrawColor(game.getRenderer()->get(), 255, 255, 255, 40);
                    SDL_Rect overlay = {0, 0, windowW, windowH};
                    SDL_RenderFillRect(game.getRenderer()->get(), &overlay);
                    gameOverImage.draw();
                    restart.drawwithImage();
                    gameExit.drawwithImage();
                    game.getRenderer()->present();
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
            // 获取玩家鱼体积（例如取宽高的平均值）
            int playerSize = (playerFish.getRect().w + playerFish.getRect().h) / 2;

            // 初始化或补充AI鱼时传入玩家体积
            aiFishes.push_back(
                    lx::AIFish::createRandomFish(game.getRenderer(), fishTypes, windowW, windowH, gen, playerSize));
        }

        // 更新分数显示

        scoreStr = "Score: " + std::to_string(scoreManager.getScore()) +
                               "  High: " + std::to_string(scoreManager.getHighScore());
        //scoreText.setAll(game.getRenderer(), {windowW / 2 - 180, 50, 360, 40}, textColor, font, SDL_BLENDMODE_BLEND,scoreStr);
        // scoreText.setRect({windowW / 2 - 180, 50, 360, 40});
        scoreText.setText(scoreStr);  // 更新分数文本内容

        // 渲染登录界面元素
        if (!isLogin)
        {
            loginUi.getRenderer()->clear();
            loginBackground.draw();
            login.drawwithImage();
            exit.drawwithImage();
            loginText.draw();
            loginUi.getRenderer()->present();
        }
        // 渲染游戏界面元素
        if (isLogin && playerFish.isAlive())
        {

        game.getRenderer()->clear();
        background.draw();
        scoreBoard.draw();
        scoreText.draw();
        playerFish.render();
        fullscreenBtn.drawwithImage();
        pauseButton.drawwithImage();
        for (auto& aiFish: aiFishes) aiFish.render();
        // 显示渲染结果
        game.getRenderer()->present();
        }
        // 结束当前帧
        game.frameEnd();
    }

    // 游戏结束处理：保存分数和清理资源
    scoreManager.saveHighScore();
    TTF_CloseFont(font);
    game.clean();
    loginUi.clean();
    return 0;
}