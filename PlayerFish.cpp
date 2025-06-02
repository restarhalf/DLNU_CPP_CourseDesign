#include "PlayerFish.h"

namespace lx 
{

    PlayerFish::PlayerFish(float x, float y)
        : Fish(x, y, 20.0f) 
	{
        float baseSpeed = 3.0f / (size * 0.3f);    // 计算速度分量
        velocity.x =baseSpeed;
        velocity.y =baseSpeed;

    } // 默认大小,请ui和算法根据实际需求调整

    void PlayerFish::move() 
    {
        position.x += velocity.x;
        position.y += velocity.y;//位置更新
        position.x = std::max(0.0f, std::min(position.x, screenWidth - size));//边界处理
        position.y = std::max(0.0f, std::min(position.y, screenHeight - size));
    }

    void PlayerFish::handleInput(char key) 
    {
        switch (key) 
        {
        case 'w': velocity.y = -2; break; // 上
        case 's': velocity.y = 2; break; // 下
        case 'a': velocity.x = -2; break; // 左
        case 'd': velocity.x = 2; break; // 右
        }
    }

    void PlayerFish::stop() 
    {
        velocity = { 0, 0 };
    }

}
