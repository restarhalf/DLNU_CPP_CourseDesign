// �̳�Fish��ʵ���Զ��ƶ���Ϊ

#pragma once
#include "Fish.h"

namespace lx 
{
    class AIFish : public Fish 
    {
    public:
        AIFish(float x, float y);//�㷨��size����ɾ�ˣ���Ϊ����size���
        void move() override;  // ��д�ƶ��߼����Զ�����λ��

    private:
        void updataVelocity()const;
    };

}
