#pragma once
#include "AIFish.h"
#include "Controller.h"
#include "Fish.h"
#include "ScoreManager.h"

namespace lx
{

    // 玩家控制的鱼类，继承自Fish
    class PlayerFish : public Fish
    {
    public:
        // 构造函数，初始化玩家鱼的位置和图片
        PlayerFish(lyt::Renderer* renderer, const std::string& imagePath, int x, int y, int w, int h);

        // 更新玩家鱼的位置和状态
        void update(int windowW, int windowH) override;
        // 处理输入控制（键盘或鼠标）
        void handleInput(const lyt::Controller* controller);
        // 尝试吃掉AI鱼，成功则加分
        bool tryEat(AIFish& ai, ScoreManager& scoreManager);
        // 重置玩家鱼的位置
        void reset(int startX, int startY);
        void resize();
        int getDirection() const { return direction; }
        void setDirection(int dir) { direction = dir; } 
        std::string getImagePath() { return imagePath; }
        void setImagePath(const std::string& path) { imagePath = path; }
        

    private:
        int velocityX = 0;  // X方向速度
        int velocityY = 0;  // Y方向速度
        int speed     = 4;  // 移动速度
        int wMax      = 150; //最大宽度
        //int direction = 1;   // 鱼的移动方向，1表示向右，-1表示向左
        std::string imagePath;  // 鱼的图片路径

    };

}  // namespace lx
