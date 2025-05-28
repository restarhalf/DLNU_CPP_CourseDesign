#include "AIFish.h"
#include <cstdlib>

namespace lx 
{

    AIFish::AIFish(float x, float y, float s)
        : Fish(x, y, s) 
    {
        // 初始化随机速度，-1,0,1方向
        //此处请算法自行修改！！！！！！！！！！！！！！！！！！
        velocity = { (rand() % 3 - 1) * 1.0f, (rand() % 3 - 1) * 1.0f };
    }
    
    void AIFish::move() 
    {
        position.x += velocity.x;
        position.y += velocity.y;
    }

}
