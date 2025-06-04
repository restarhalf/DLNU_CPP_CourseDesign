#include "PlayerFish.h"
#include "ScoreManager.h"
#include <SDL.h>

namespace lx {

    // 玩家鱼构造函数
    PlayerFish::PlayerFish(lyt::Renderer* renderer, const std::string& imagePath, int x, int y, int w, int h)
        : Fish(renderer, imagePath, x, y, w, h) {
    }

    // 处理玩家输入，控制鱼的移动方向
    void PlayerFish::handleInput(const lyt::Controller* controller) {
        velocityX = velocityY = 0;
        if (controller->isKeyPressed(SDL_SCANCODE_W)) velocityY = -speed;
        if (controller->isKeyPressed(SDL_SCANCODE_S)) velocityY = speed;
        if (controller->isKeyPressed(SDL_SCANCODE_A)) velocityX = -speed;
        if (controller->isKeyPressed(SDL_SCANCODE_D)) velocityX = speed;
        //实现同时按两个移动按键的要求
    }

    // 更新玩家鱼的位置，并进行边界检测
    void PlayerFish::update(int windowW, int windowH) {
        rect.x += velocityX;
        rect.y += velocityY;

        // 边界检测，防止鱼游出窗口
        if (rect.x < 0) rect.x = 0;
        if (rect.y < 0) rect.y = 0;
        if (rect.x + rect.w > windowW) rect.x = windowW - rect.w;//鱼中心点加上其体积宽高的延伸是否超出边界
        if (rect.y + rect.h > windowH) rect.y = windowH - rect.h;
    }

    bool PlayerFish::tryEat(AIFish& aiFish, ScoreManager& scoreManager)
    {
        if (!aiFish.isAlive() || !alive) return false;
        SDL_Rect other = aiFish.getRect();
        if (SDL_HasIntersection(&rect, &other)) {
            float mySize = getSize();
            float otherSize = aiFish.getSize();

            if (mySize > otherSize * 1.2f) {
                // 玩家比 AI 鱼大 20% 以上，可以吞掉
                aiFish.kill();
                if (mySize < SizeMax)//鱼体积不超过最大限制
                grow(1.02f);  // 体型增长 5%，否则不继续长大保证游戏时长，先修改为2%
                int value = aiFish.getScoreValue();
                scoreManager.add(value);          //加分     
                SDL_Log("吃掉AI鱼，得分 +%d，当前体型 %.2f", value, getSize());
                return true;
            }
            else if (mySize < otherSize * 0.8f) {
                // 玩家比 AI 鱼小 20% 以上，被吃掉
                alive = false;
                SDL_Log("被更大的AI鱼吃掉，游戏结束！");
            }
            else {
                // 大小相近，不处理
                SDL_Log("碰撞但大小相近，无操作");//是否会太花哨？
            }
        }

        return false;
    }


    // 重置玩家鱼的位置和状态
    void PlayerFish::reset(int startX, int startY) {
        rect.x = startX;
        rect.y = startY;
        rect.w = rect.h = 60;//初始体格
        alive = true;
    }

} // namespace lx
