#include "PlayerFish.h"

namespace lx 
{

    PlayerFish::PlayerFish(float x, float y)
        : Fish(x, y, 20.0f) 
	{
        float baseSpeed = 3.0f / (size * 0.3f);    // �����ٶȷ���
        velocity.x =baseSpeed;
        velocity.y =baseSpeed;

    } // Ĭ�ϴ�С,��ui���㷨����ʵ���������

    void PlayerFish::move() 
    {
        position.x += velocity.x;
        position.y += velocity.y;//λ�ø���
        position.x = std::max(0.0f, std::min(position.x, screenWidth - size));//�߽紦��
        position.y = std::max(0.0f, std::min(position.y, screenHeight - size));
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
