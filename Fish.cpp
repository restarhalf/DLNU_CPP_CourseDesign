#include "Fish.h"
#include <cmath>

namespace lx 
{

    

    void Fish::checkBounds()const {
        bool hitBoundary = false;//默认未撞边界

        // 左右边界检测
        if (position.x <= 0 || position.x >= screenWidth - size) {
            hitBoundary = true;
        }

        // 上下边界检测
        if (position.y <= 0 || position.y >= screenHeight - size) {
            hitBoundary = true;
        }
        return hitBoundary;
    }
    float getDistance(Vector2 a, Vector2 b) //获取两鱼位置距离
    {
        return std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
    }

    Fish::Fish(float x, float y, float s)
        : position{ x, y }, size(s), velocity{ 0, 0 } 
    {}

    Fish::~Fish() {}

    bool Fish::checkCollision(const Fish& other) const //吃食距离判断
    {
        return getDistance(position, other.position) < (size + other.size);
    }

    bool Fish::canEat(const Fish& other) const //吃食体积判断
    {
        return size > other.size;
    }

    Vector2 Fish::getPosition() const 
    {
        return position;
    }

    float Fish::getSize() const 
    {
        return size;
    }

    Vector2 Fish::getVelocity() const 
    {
        return velocity;
    }

    void Fish::grow(float amount) 
    {
        size += amount;
    }

    void Fish::setVelocity(Vector2 v) 
    {
        velocity = v;
    }

}