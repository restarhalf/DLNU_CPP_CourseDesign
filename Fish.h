#pragma once

// ���λ�á���С���ٶȵ�����
// �����ƶ�����ײ��⡢��ʳ�ж��Ƚӿ�
#include <cmath>

namespace lx 
{

    // ����:������ٶ�
    struct Vector2 
    {
        float x, y;
    };

    // ������������
    float getDistance(Vector2 a, Vector2 b);

    // Fish������
    class Fish 
    {
    protected:
        Vector2 position; // λ��
        Vector2 velocity; // �ٶ�
        float size;       // ��С

    public:
        Fish(float x, float y, float s);  
        virtual ~Fish();                  // ����̳�

        virtual void move() = 0;          // ����ʵ���ƶ��߼�
       
        void checkBounds()const;                 //���߽���

        bool checkCollision(const Fish& other) const;  // ��ײ��⣨��
        bool canEat(const Fish& other) const;          // �ж��Ƿ��ܳԵ���һ����

        Vector2 getPosition() const;     // ��ȡ��ǰλ��
        float getSize() const;           // ��ȡ��С
        Vector2 getVelocity() const;     // ��ȡ�ٶ�

        void grow(float amount);         // �������
        void setVelocity(Vector2 v);    // �����ٶ�
    };

} 

