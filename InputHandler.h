#pragma once
//������������¼�������������ƶ�
#include "PlayerFish.h"

namespace lx 
{

    class InputHandler 
    {
    private:
        PlayerFish* player; // ָ��������ָ��

    public:
        InputHandler(PlayerFish* p);   // ���캯����������������ָ��
        void processInput(char key);   // ��������
        void stopMovement();           // ֹͣ����ƶ�
    };
    //δ���
} 
