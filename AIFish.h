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
