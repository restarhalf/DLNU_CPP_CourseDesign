// 继承Fish，实现自动移动行为

#pragma once
#include "Fish.h"

namespace lx 
{
    class AIFish : public Fish 
    {
    public:
        AIFish(float x, float y, float size);
        void move() override;  // 重写移动逻辑，自动更新位置
    };

}
