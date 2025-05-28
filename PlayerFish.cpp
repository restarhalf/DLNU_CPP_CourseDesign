#include "PlayerFish.h"

namespace lx 
{

    PlayerFish::PlayerFish(float x, float y)
        : Fish(x, y, 20.0f) 
	{} // 默认大小,请ui和算法根据实际需求调整

    void PlayerFish::move() 
    {
        position.x += velocity.x;
        position.y += velocity.y;
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
