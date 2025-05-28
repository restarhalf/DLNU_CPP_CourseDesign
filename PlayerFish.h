// 继承Fish，增加玩家输入响应

#pragma once
#include "Fish.h"

namespace lx 
{
    class PlayerFish : public Fish 
    {
    public:
        PlayerFish(float x, float y);
        void move() override;           // 重写移动函数，使用速度更新位置
        void handleInput(char key);     // 根据键盘输入更新速度方向
        void stop();                    // 停止移动，速度置零
    };

} 
