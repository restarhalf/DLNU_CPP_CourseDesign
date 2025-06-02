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
        // ��ʼ�ٶȣ�����������ٶ����С�ɷ��ȣ�
        //�˴����㷨�����޸ģ�������������������������������������֪����֪�����ڸ���
        size = 10.0f + static_cast<float>(rand() % 91); // 10-100�����С
        updateVelocity();//����ٶȸ�����
    }
    
    void AIFish::move() 
    {
        //�߽���
        //���߽�������·���

        if (checkBounds()) {
            updataVelocity();
        }

        //����λ��
        position.x += velocity.x;
        position.y += velocity.y;
        //��֤�����߽�
        position.x = std::max(0.0f, std::min(position.x, screenWidth - size));
        position.y = std::max(0.0f, std::min(position.y, screenHeight - size));

    }
  
    void AIFish::updataVelocity()const
    {
        // ����ı䷽�����ٶ����С�ɷ���
        float baseSpeed = 3.0f / (size * 0.3f);
        // ������򣨽Ƕȣ�0-2�У�
        float angle = (rand() % 360) * 3.1415926f / 180.0f;

        // �����ٶȷ���
        velocity.x = std::cos(angle) * baseSpeed;
        velocity.y = std::sin(angle) * baseSpeed;

        // ������С�ٶȣ����������ȫ��ֹ...��
        float minSpeed = 0.3f;
        float currentSpeed = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
        if (currentSpeed < minSpeed) {
            velocity.x = (velocity.x / currentSpeed) * minSpeed;
            velocity.y = (velocity.y / currentSpeed) * minSpeed;
        }
    }
}