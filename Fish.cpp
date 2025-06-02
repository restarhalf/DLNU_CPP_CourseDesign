#include "Fish.h"
#include <cmath>

namespace lx 
{

    

    void Fish::checkBounds()const {
        bool hitBoundary = false;//Ĭ��δײ�߽�

        // ���ұ߽���
        if (position.x <= 0 || position.x >= screenWidth - size) {
            hitBoundary = true;
        }

        // ���±߽���
        if (position.y <= 0 || position.y >= screenHeight - size) {
            hitBoundary = true;
        }
        return hitBoundary;
    }
    float getDistance(Vector2 a, Vector2 b) //��ȡ����λ�þ���
    {
        return std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
    }

    Fish::Fish(float x, float y, float s)
        : position{ x, y }, size(s), velocity{ 0, 0 } 
    {}

    Fish::~Fish() {}

    bool Fish::checkCollision(const Fish& other) const //��ʳ�����ж�
    {
        return getDistance(position, other.position) < (size + other.size);
    }

    bool Fish::canEat(const Fish& other) const //��ʳ����ж�
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