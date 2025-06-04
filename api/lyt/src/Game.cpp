//
// Created by restarhalf on 2025/5/28.
//
#include "Game.h"
namespace lyt
{
    int Game::num = 0;
    // 默认构造函数，初始化基本属性
    Game::Game() : window(nullptr), renderer(nullptr), isRunning(false) {}

    // 析构函数，清理游戏资源
    Game::~Game() {}

    // 初始化游戏环境和事件
    bool Game::init(const std::string &title, int width, int height, int flags)
    {
        num++;
        // 初始化SDL所有子系统
        if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        {
            SDL_Log("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
            isRunning = false;
            return false;
        }
        else
        {
            SDL_Log("SDL initialized");
            isRunning = true;
        }


        // 初始化TTF字体系统
        if (TTF_Init() == -1)
        {
            SDL_Log("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
            isRunning = false;
            return false;
        }
        else
        {
            SDL_Log("SDL_TTF initialized");
        }

        // 初始化图像系统
        if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == 0)
        {
            SDL_Log("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
            isRunning = false;
            return false;
        }
        else
        {
            SDL_Log("IMG initialized");
        }
        // 创建游戏窗口
        try
        {
            window = new Window(title, width, height);
            SDL_Log("Window created");
        }
        catch (const std::runtime_error &e)
        {
            SDL_Log("Window could not be created! SDL_Error: %s\n", e.what());
            isRunning = false;
            return false;
        }

        // 创建渲染器
        try
        {
            renderer = new Renderer(window, true);
            SDL_Log("Renderer created");
        }
        catch (const std::runtime_error &e)
        {
            SDL_Log("Renderer could not be created! SDL_Error: %s\n", e.what());
            if (window)
            {
                delete window;
                window = nullptr;
            }
            isRunning = false;
            return false;
        }
        return isRunning;
    }

    // 处理游戏事件
    void Game::handleEvent(SDL_Event &event, int &x, int &y)
    {
        // 检查退出事件（窗口关闭或ESC键）
        if (event.type == SDL_QUIT || (event.key.keysym.sym == SDLK_ESCAPE && event.type == SDL_KEYDOWN))
        {
            clean();
            isRunning = false;
            return;
        }
        // 处理控制器事件和窗口事件
        controller.event(event, x, y);
        window->handleEvents(event);
    }

    // 清理游戏资源
    void Game::clean()
    {
        num--;
        if (renderer) delete renderer;
        if (window) delete window;

        SDL_Quit();
        IMG_Quit();
        TTF_Quit();

        SDL_Log("Game cleaned");
        if (num == 0) exit(0);
    }

    // 更新游戏状态
    void Game::update()
    {
        if (renderer)
        {
            renderer->clear();
            renderer->present();
        }
    }

    // 渲染游戏画面
    void Game::render() const
    {
        if (renderer)
        {
            renderer->clear();
            renderer->present();
        }
    }

    // 检查游戏是否正在运行
    bool Game::running() const { return isRunning; }

    // 开始帧计时
    void Game::frameStart() { Start = SDL_GetTicks(); }

    // 结束帧计时并控制帧率
    void Game::frameEnd()
    {
        Time = SDL_GetTicks() - Start;
        if (Time - static_cast<Uint32>(FPS) < 0)
        {
            SDL_Delay(static_cast<Uint32>(FPS) - Time);
        }
    }

    // 设置游戏帧率
    void Game::setFps(const float fps) { FPS = 1000.f / fps; }

    // Getters and setters
    Renderer *Game::getRenderer() const { return renderer; }
    Window   *Game::getWindow() const { return window; }
    void      Game::setRenderer(Renderer *renderer) { this->renderer = renderer; }
    void      Game::setWindow(Window *window) { this->window = window; }
}  // namespace lyt
