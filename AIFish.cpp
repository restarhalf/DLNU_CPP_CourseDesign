#include "AIFish.h"
#include <cstdlib>

namespace lx 
{

    AIFish::AIFish(float x, float y, float s)
        : Fish(x, y, s) 
    {
        // ��ʼ������ٶȣ�-1,0,1����
        //�˴����㷨�����޸ģ�����������������������������������
        velocity = { (rand() % 3 - 1) * 1.0f, (rand() % 3 - 1) * 1.0f };
    }
    
    void AIFish::move() 
    {
        position.x += velocity.x;
        position.y += velocity.y;
    }

}
