#include "PlayerFish.h"

namespace lx 
{

    PlayerFish::PlayerFish(float x, float y)
        : Fish(x, y, 20.0f) 
	{} // Ĭ�ϴ�С,��ui���㷨����ʵ���������

    void PlayerFish::move() 
    {
        position.x += velocity.x;
        position.y += velocity.y;
    }

    void PlayerFish::handleInput(char key) 
    {
        switch (key) 
        {
        case 'w': velocity.y = -2; break; // ��
        case 's': velocity.y = 2; break; // ��
        case 'a': velocity.x = -2; break; // ��
        case 'd': velocity.x = 2; break; // ��
        }
    }

    void PlayerFish::stop() 
    {
        velocity = { 0, 0 };
    }

}
