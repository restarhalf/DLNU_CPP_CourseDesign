//
// Created by restarhalf on 2025/5/28.
//
#ifndef CLIENTSIDE_H
#define CLIENTSIDE_H
#include<SDL.h>
#include<string>

class Game {
    //-----------------------------------------------------//
    //窗口部分
private:
    //窗口
    SDL_Window *window;
    //渲染器
    SDL_Renderer *renderer;
    //是否运行判断器
    bool isRunning;

public:
    //构造函数和析构函数
    Game();

    ~Game();

    //初始化函数
    bool init(const std::string &title, int width, int height, int flags);

    //事件处理函数
    void handleEvents();

    //清理函数
    void clean() const;

    //状态更新
    void update();

    //渲染函数
    void render() const;

    //运行状态判断器
    bool running() const;

    //-----------------------------------------------------//
    //帧率部分
private:
    //帧率//后面那个60是帧率
    const float FPS = 1000 / 60.f;
    //初始时间
    Uint32 Start = 0;
    //经历的时间
    Uint32 Time = 0;

public:
    void frameStart();

    void frameEnd();

    SDL_Renderer *getRenderer() const;

    SDL_Window *getWindow() const;
};
#endif //CLIENTSIDE_H
