//
// Created by restarhalf on 2025/5/28.
//
#ifndef CLIENTSIDE_H
#define CLIENTSIDE_H
#include "Window.h"
#include "Renderer.h"
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include<string>

namespace lyt {
    class Game {
        //-----------------------------------------------------//
        //窗口部分
    private:
        // 窗口管理
        Window *window;
        // 渲染器管理
        Renderer *renderer;
        //是否运行判断器
        bool isRunning;

    public:
        //构造函数和析构函数
        Game();

        ~Game();

        //初始化函数
        bool init(std::string title, int width, int height, int flags);

        //事件处理函数
        void handleEvents();

        //清理函数
        void clean() const;

        //状态更新
        void update();

        //渲染函数
        void render() const;

        Renderer *getRenderer() const;

        Window *getWindow() const;

        TTF_Font *getFont() const;

        void setRenderer(Renderer *renderer);

        void setWindow(Window *window);

        void setFont(Renderer *renderer, const std::string &fontPath, int fontSize);

        //运行状态判断器
        [[nodiscard]] bool running() const;

        //-----------------------------------------------------//
        //帧率部分
    private:
        //帧率//后面那个60是帧率
        float FPS = 1000 / 165.f;
        //初始时间
        Uint32 Start = 0;
        //经历的时间
        Uint32 Time = 0;
        //字体
        TTF_Font *font;

    public:
        void frameStart();

        void frameEnd();

        void setFps(float fps);
    };
}

#endif //CLIENTSIDE_H
