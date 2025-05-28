#pragma once

namespace lx 
{

    // 管理游戏运行状态，菜单、游戏中、暂停、结束
    class GameState 
    {
    public:
        enum State { MENU, RUNNING, PAUSED, GAME_OVER }; 

    private:
        State cur; // 当前状态

    public:
        GameState();
        void setState(State s); // 设置状态
        State getState() const; // 获取状态
        bool isRunning() const; // 判断游戏是否正在运行
    };

}