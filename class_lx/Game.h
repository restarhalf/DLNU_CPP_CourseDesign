#pragma once
//
// Created by restarhalf on 2025/5/28.
//
#ifndef GAME_H
#define GAME_H
#include "Button.h"
#include "Controller.h"
#include "Renderer.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "Window.h"
#include <bits/stdc++.h>

namespace lyt
{
    /**
     * @brief 游戏类，负责管理游戏的主要功能和生命周期
     */
    class Game
    {
    private:
        // 窗口部分
        Window* window;  ///< 游戏窗口指针
        Renderer* renderer;  ///< 渲染器指针
        bool       isRunning;  ///< 游戏运行状态标志
        Controller controller;  ///< 控制器对象

        // 帧率控制部分
        float  FPS = 1000 / 165.f;  ///< 帧率（默认165FPS）
        Uint32 rendererFlags = SDL_RENDERER_PRESENTVSYNC;  ///< 渲染器标志
        Uint32 Start = 0;  ///< 帧开始时间
        Uint32 Time = 0;  ///< 帧经过的时间

    public:
        /**
         * @brief 默认构造函数
         */
        Game();

        /**
         * @brief 析构函数，负责清理游戏资源
         */
        ~Game();

        /**
         * @brief 初始化游戏
         * @param title 窗口标题
         * @param width 窗口宽度
         * @param height 窗口高度
         * @param flags SDL初始化标志
         * @return 初始化是否成功
         */
        bool init(std::string title, int width, int height, int flags);

        /**
         * @brief 处理游戏事件
         * @param event SDL事件对象
         * @param x 鼠标x坐标
         * @param y 鼠标y坐标
         */
        void handleEvent(SDL_Event& event, int& x, int& y);

        /**
         * @brief 清理游戏资源
         */
        void clean();

        /**
         * @brief 更新游戏状态
         */
        void update() const;

        /**
         * @brief 渲染游戏画面
         */
        void render() const;

        // Getters and setters
        Renderer* getRenderer() const;
        Window* getWindow() const;
        void               setRenderer(Renderer* renderer);
        void               setWindow(Window* window);
        [[nodiscard]] bool running() const;

        /**
         * @brief 开始帧计时
         */
        void frameStart();

        /**
         * @brief 结束帧计时并进行帧率控制
         */
        void frameEnd();

        /**
         * @brief 设置目标帧率
         * @param fps 目标帧率
         */
        void setFps(float fps);
    };
}  // namespace lyt

#endif  // GAME_H