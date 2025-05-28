//
// Created by restarhalf on 2025/5/28.
//
#ifndef CLIENTSIDE_H
#define CLIENTSIDE_H
#include<SDL.h>
#include<string>
class Game {
private:
    //窗口
    SDL_Window* window;
    //渲染器
    SDL_Renderer* renderer;
    //是否运行判断器
    bool isRunning;
public:
    //构造函数和析构函数
    Game();
    ~Game();
    //初始化函数
    bool init(const std::string& title,int width,int height,int flags);
    //事件处理函数
    void handleEvents();
    //清理函数
    void clean();
    //状态更新
    void update();
    //渲染函数
    void render();
    //运行状态判断器
    bool running();
};

#endif //CLIENTSIDE_H
