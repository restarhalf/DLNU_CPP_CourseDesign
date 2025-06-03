#pragma once
//处理玩家输入事件，控制玩家鱼移动
#include "PlayerFish.h"

namespace lx 
{

    class InputHandler 
    {
    private:
        PlayerFish* player; // 指向玩家鱼的指针

    public:
        InputHandler(PlayerFish* p);   // 构造函数，传入玩家鱼对象指针
        void processInput(char key);   // 键盘输入
        void stopMovement();           // 停止玩家移动
    };
    //未完成
} 
