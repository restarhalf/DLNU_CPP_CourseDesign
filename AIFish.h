// 继承Fish，实现自动移动行为

#pragma once
#include "Fish.h"

namespace lx 
{
    class AIFish : public Fish 
    {
    public:
        AIFish(float x, float y);//算法把size参数删了，因为它们size随机
        void move() override;  // 重写移动逻辑，自动更新位置

    private:
        void updataVelocity()const;
    };

}


#ifndef AIFISH_H  // 如果没有定义 AIFISH_H（防止头文件被重复包含）
#define AIFISH_H

#include "Fish.h"  // 包含 Fish 类的头文件

namespace lx {  // 定义命名空间 lx

    class AIFish : public Fish {  // 定义 AIFish 类，公有继承自 Fish 类
    public:
        // 构造函数，接受渲染器指针、鱼的坐标和尺寸
        AIFish(SDL_Renderer* renderer, int x, int y, int width, int height);

        // 重写（override）基类 Fish 的 update 方法，用于更新鱼的状态
        void update(int windowW, int windowH) override;

        // 重写（override）基类 Fish 的 tryEat 方法，用于尝试让鱼吃其他鱼
        bool tryEat(Fish& other) override;

    private:
        float vx;  // 私有成员变量，表示鱼在 x 方向的速度

        // 私有成员函数，用于反转鱼的运动方向
        void reverseDirection();
    };

} // namespace lx

#endif
