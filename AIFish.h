// �̳�Fish��ʵ���Զ��ƶ���Ϊ

#pragma once
#include "Fish.h"

namespace lx 
{
    class AIFish : public Fish 
    {
    public:
        AIFish(float x, float y, float size);
        void move() override;  // ��д�ƶ��߼����Զ�����λ��
    };

}
