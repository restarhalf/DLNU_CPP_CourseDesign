/**
 * @file PlayerFish.cpp
 * @brief 玩家控制的鱼类实现
 */

#include "PlayerFish.h"

#include <SDL.h>

#include "ScoreManager.h"

namespace lx
{

    /**
     * @brief 玩家鱼构造函数
     * @param renderer 渲染器指针
     * @param imagePath 图片路径
     * @param x 初始x坐标
     * @param y 初始y坐标
     * @param w 宽度
     * @param h 高度
     */
    PlayerFish::PlayerFish(lyt::Renderer* renderer, const std::string& imagePath, int x, int y, int w, int h) :
        Fish(renderer, imagePath, x, y, w, h)
    {
    }

    /**
     * @brief 处理玩家输入控制
     * @param controller 控制器指针
     */
    void PlayerFish::handleInput(const lyt::Controller* controller)
    {
        velocityX = velocityY = 0;
        if (controller->isKeyPressed(SDL_SCANCODE_W)) velocityY = -speed;
        if (controller->isKeyPressed(SDL_SCANCODE_S)) velocityY = speed;
        if (controller->isKeyPressed(SDL_SCANCODE_A))
        {
            velocityX = -speed;
            setDirection(-1);
        }
        if (controller->isKeyPressed(SDL_SCANCODE_D))
        {
            velocityX = speed;
            setDirection(1);
        }
    }


    /**
     * @brief 更新玩家鱼的位置，并进行边界检测
     * @param windowW 窗口宽度
     * @param windowH 窗口高度
     */
    void PlayerFish::update(int windowW, int windowH)
    {
        rect.x += velocityX;
        rect.y += velocityY;

        // 边界检测，防止鱼游出窗口
        if (rect.x < 0) rect.x = 0;
        if (rect.y < windowW*0.07) rect.y = windowW*0.07;
        if (rect.x + rect.w > windowW) rect.x = windowW - rect.w;
        if (rect.y + rect.h > windowH) rect.y = windowH - rect.h;
    }

    /**
     * @brief 尝试吃掉AI鱼，成功则加分
     * @param aiFish AI鱼对象引用
     * @param scoreManager 分数管理器引用
     * @return 是否成功吃掉AI鱼
     */
    bool PlayerFish::tryEat(AIFish& aiFish, ScoreManager& scoreManager)
    {
        SDL_Rect other = aiFish.getRect();
        if (SDL_HasIntersection(&rect, &other))
        {
            float mySize    = getSize();
            float otherSize = aiFish.getSize();

            if (mySize > otherSize * 1.1f)
            {
                // 玩家比 AI 鱼大 10% 以上，可以吞掉
                aiFish.kill();
                float predictedSize = getSize() * 1.04f;  // 模拟增长后的体积
                if (sqrt(predictedSize) <= wMax)
                {
                    grow(1.02f);  // 安全才实际增长
                }
                else
                {
                    resize();
                }
                int value = aiFish.getScoreValue();
                if (aiFish.getspecialValue() > 4)  // 六分之一的概率
                {
                    value += value / 2;  // 奖励部分
                    scoreManager.add(value);
                    SDL_Log("吃掉奖励鱼，得分 +%d，当前体型 %.2f", value, getSize());
                }
                else
                {
                    scoreManager.add(value);
                    SDL_Log("吃掉小鱼，得分 +%d，当前体型 %.2f", value, getSize());
                }
                return true;
            }
            else if (mySize < otherSize * 0.9f)
            {
                // 玩家比 AI 鱼小 20% 以上，被吃掉
                alive = false;
            }
        }

        return false;
    }


    /**
     * @brief 重置玩家鱼的位置和状态
     * @param startX 起始X坐标
     * @param startY 起始Y坐标
     */
    void PlayerFish::reset(int startX, int startY)
    {
        rect.x = startX;
        rect.y = startY;
        rect.w = rect.h = 60;
        alive           = true;
    }

    /**
     * @brief 调整玩家鱼大小至最大值
     */
    void PlayerFish::resize()
    {
        rect.w = wMax;
        rect.h = wMax;
    }
}  // namespace lx
