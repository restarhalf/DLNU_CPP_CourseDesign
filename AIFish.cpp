#include "AIFish.h"
#include <cstdlib>
#include<ctime>
#include<algorithm>
namespace lx 
{

    AIFish::AIFish(float x, float y)
        : Fish(x, y, 0) 
    {
        std::srand(static_cast<unsigned>(std::time(nullptr)));
        // 初始速度（方向随机，速度与大小成反比）
        //此处请算法自行修改！！！！！！！！！！！！！！！！！！，知道了知道了在改了
        size = 10.0f + static_cast<float>(rand() % 91); // 10-100随机大小
        updateVelocity();//随机速度跟方向
    }
    
    void AIFish::move() 
    {
        //边界检测
        //到边界随机更新方向

        if (checkBounds()) {
            updataVelocity();
        }

        //更新位置
        position.x += velocity.x;
        position.y += velocity.y;
        //保证不出边界
        position.x = std::max(0.0f, std::min(position.x, screenWidth - size));
        position.y = std::max(0.0f, std::min(position.y, screenHeight - size));

    }
  
    void AIFish::updataVelocity()const
    {
        // 随机改变方向且速度与大小成反比
        float baseSpeed = 3.0f / (size * 0.3f);
        // 随机方向（角度，0-2π）
        float angle = (rand() % 360) * 3.1415926f / 180.0f;

        // 计算速度分量
        velocity.x = std::cos(angle) * baseSpeed;
        velocity.y = std::sin(angle) * baseSpeed;

        // 限制最小速度（避免大鱼完全静止...）
        float minSpeed = 0.3f;
        float currentSpeed = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
        if (currentSpeed < minSpeed) {
            velocity.x = (velocity.x / currentSpeed) * minSpeed;
            velocity.y = (velocity.y / currentSpeed) * minSpeed;
        }
    }
}