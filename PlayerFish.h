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
#ifndef PLAYERFISH_H  // 如果未定义 PLAYERFISH_H（防止头文件重复包含的预编译指令）
#define PLAYERFISH_H

#include "Fish.h"  // 包含 Fish 类的头文件，因为 PlayerFish 继承自 Fish

namespace lx {  // 定义命名空间 lx

    class PlayerFish : public Fish {  // PlayerFish 类，公有继承自 Fish 类
    public:
        // 构造函数，接受渲染器指针、鱼的坐标和尺寸
        PlayerFish(SDL_Renderer* renderer, int x, int y, int width, int height);

        // 重写基类 Fish 的 update 方法，用于更新鱼的状态（窗口宽高作为参数，可能用于边界检测等）
        void update(int windowW, int windowH) override;

        // 重写基类 Fish 的 tryEat 方法，用于尝试让鱼吃其他鱼（参数为另一条 Fish 的引用）
        bool tryEat(Fish & other) override;

        // 控制鱼向上移动的方法，pressed 表示是否按下移动键（布尔值，true 表示按下）
        void moveUp(bool pressed);
        // 控制鱼向下移动的方法，pressed 表示是否按下移动键（布尔值，true 表示按下）
        void moveDown(bool pressed);
        // 控制鱼向左移动的方法，pressed 表示是否按下移动键（布尔值，true 表示按下）
        void moveLeft(bool pressed);
        // 控制鱼向右移动的方法，pressed 表示是否按下移动键（布尔值，true 表示按下）
        void moveRight(bool pressed);

        // 判断鱼是否死亡的常量成员函数（不会修改对象状态）
        bool isDead() const;

    private:
        // 记录鱼是否向上移动的布尔变量
        bool movingUp;
        // 记录鱼是否向下移动的布尔变量
        bool movingDown;
        // 记录鱼是否向左移动的布尔变量
        bool movingLeft;
        // 记录鱼是否向右移动的布尔变量
        bool movingRight;
        // 鱼移动的速度（整数类型，可根据实际需求调整为合适类型，如浮点数等）
        int speed;
        // 记录鱼是否死亡的布尔变量
        bool dead;
    };

} // namespace lx

#endif
