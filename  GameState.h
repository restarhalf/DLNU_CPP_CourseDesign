#pragma once

namespace lx 
{

    // ������Ϸ����״̬���˵�����Ϸ�С���ͣ������
    class GameState 
    {
    public:
        enum State { MENU, RUNNING, PAUSED, GAME_OVER }; 

    private:
        State cur; // ��ǰ״̬

    public:
        GameState();
        void setState(State s); // ����״̬
        State getState() const; // ��ȡ״̬
        bool isRunning() const; // �ж���Ϸ�Ƿ���������
    };

}