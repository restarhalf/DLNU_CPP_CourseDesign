// �̳�Fish���������������Ӧ

#pragma once
#include "Fish.h"

namespace lx 
{
    class PlayerFish : public Fish 
    {
    public:
        PlayerFish(float x, float y);
        void move() override;           // ��д�ƶ�������ʹ���ٶȸ���λ��
        void handleInput(char key);     // ���ݼ�����������ٶȷ���
        void stop();                    // ֹͣ�ƶ����ٶ�����
    };

} 
