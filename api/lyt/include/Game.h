//
// Created by restarhalf on 2025/5/28.
//
#ifndef GAME_H
#define GAME_H
#include <Button.h>
#include <Controller.h>
#include <Renderer.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <Window.h>
#include <bits/stdc++.h>

namespace lyt
{
    class Game
    {
        //-----------------------------------------------------//
        // 窗口部分
    private:
        // 窗口管理
        Window *window;
        // 渲染器管理
        Renderer *renderer;
        // 是否运行判断器
        bool isRunning;
        // 控制器
        Controller controller;

    public:
        // 构造函数和析构函数
        Game();

        ~Game();

        // 初始化函数
        bool init(std::string title, int width, int height, int flags);

        // 事件处理函数
        void handleEvent(SDL_Event &event, int &x, int &y);

        // 清理函数
        void clean();

        // 状态更新
        void update() const;

        // 渲染函数
        void render() const;

        Renderer *getRenderer() const;

        Window *getWindow() const;

        void setRenderer(Renderer *renderer);

        void setWindow(Window *window);

        // 运行状态判断器
        [[nodiscard]] bool running() const;

        //-----------------------------------------------------//
        // 帧率部分
    private:
        // 帧率//后面那个60是帧率
        float  FPS           = 1000 / 165.f;  // 60 FPS
        Uint32 rendererFlags = SDL_RENDERER_PRESENTVSYNC;
        // 初始时间
        Uint32 Start = 0;
        // 经历的时间
        Uint32 Time = 0;

    public:
        void frameStart();

        void frameEnd();

        void setFps(float fps);
    };
}  // namespace lyt

#endif  // GAME_H
