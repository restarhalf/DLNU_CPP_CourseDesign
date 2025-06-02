#pragma once

// 鱼的位置、大小、速度等属性
// 定义移动、碰撞检测、吃食判定等接口
#include <cmath>

namespace lx 
{

    // 向量:坐标和速度
    struct Vector2 
    {
        float x, y;
    };

    // 计算两点间距离
    float getDistance(Vector2 a, Vector2 b);

    // Fish抽象类
    class Fish 
    {
    protected:
        Vector2 position; // 位置
        Vector2 velocity; // 速度
        float size;       // 大小

    public:
        Fish(float x, float y, float s);  
        virtual ~Fish();                  // 方便继承

        virtual void move() = 0;          // 子类实现移动逻辑
       
        void checkBounds()const;                 //补边界检测

        bool checkCollision(const Fish& other) const;  // 碰撞检测（鱼
        bool canEat(const Fish& other) const;          // 判断是否能吃掉另一个鱼

        Vector2 getPosition() const;     // 获取当前位置
        float getSize() const;           // 获取大小
        Vector2 getVelocity() const;     // 获取速度

        void grow(float amount);         // 增加体积
        void setVelocity(Vector2 v);    // 设置速度
    };

} 

