/**
 * @file AIFish.cpp
 * @brief AI鱼类的实现
 */
#include "AIFish.h"

namespace lx
{

    /**
     * @brief 构造函数，初始化AI鱼的速度、方向和分数值
     */
    AIFish::AIFish(lyt::Renderer* renderer, const std::string& imagePath, int x, int y, int w, int h) :
        Fish(renderer, imagePath, x, y, w, h)
    {
        speed        = 1 + rand() % 3;  // 随机速度1~3
        direction    = (rand() % 2 == 0) ? 1 : -1;  // 添加方向初始化
        scoreValue   = std::max(1, w / 5);  // 分数值初始为宽度的1/5，至少为1
        specialValue = rand() % 6;  // 随机范围0~5
    }

    /**
     * @brief 更新AI鱼的位置，并在碰到窗口边界时反向
     */
    void AIFish::update(int windowW, int windowH)
    {
        rect.x += direction * speed;
        if (rect.x <= 0 || rect.x + rect.w >= windowW)
        {
            rect.x = std::max(0, std::min(rect.x, windowW - rect.w));  // 保持在窗口内
            kill();
        }
    }

    /**
     * @brief 设置AI鱼移动方向
     */
    void AIFish::setDirection(int dir) { direction = dir; }

    /**
     * @brief 获取AI鱼移动方向
     */
    int AIFish::getDirection() const { return direction; }

    /**
     * @brief 让AI鱼变大，并重新计算分数值
     */
    void AIFish::grow(float scale)
    {
        Fish::grow(scale);
        scoreValue = (rect.w * rect.h) / 10;
    }

    /**
     * @brief 获取AI鱼的分值
     */
    int AIFish::getScoreValue() const { return scoreValue; }

    /**
     * @brief 获取AI鱼的特殊分值
     */
    int AIFish::getspecialValue() const { return specialValue; }


    /**
     * @brief 创建随机AI鱼
     * @param renderer 渲染器指针
     * @param fishTypes 鱼类型集合
     * @param windowW 窗口宽度
     * @param windowH 窗口高度
     * @param gen 随机数生成器
     * @param playerSize 玩家鱼体积参考
     * @return 创建的AI鱼对象
     */
    AIFish AIFish::createRandomFish(lyt::Renderer* renderer, const std::vector<FishType>& fishTypes, int windowW,
                                    int windowH, std::mt19937& gen, int playerSize)
    {
        // 动态体积范围（玩家鱼的70%~130%）
        std::uniform_int_distribution<int> disSize(static_cast<int>(playerSize * 0.7),
                                                   static_cast<int>(playerSize * 1.3));
        int size = std::clamp(disSize(gen), 20, 120);

        // 确定生成位置和方向
        int side = gen() % 2;
        int x    = (side == 0) ? 0 : windowW - size;
        int minY = static_cast<int>(windowH * 0.1f);
        int maxY = windowH - size;
        if (maxY < minY) maxY = minY;  // 处理窗口过小的情况
        std::uniform_int_distribution<int> disY(minY, maxY);  // 计分板处不生成鱼
        int y = disY(gen);

        // 根据体积选择鱼类类型
        const FishType* selectedType = nullptr;
        for (const auto& type: fishTypes)
        {
            if (size >= type.minSize && size <= type.maxSize)
            {
                selectedType = &type;
                break;
            }
        }
        if (!selectedType) selectedType = &fishTypes[0];  // 默认使用第一个类型

        // 选择纹理
        std::string texturePath;
        if (selectedType->textures.empty())
        {
            texturePath = "asset/images/fish2_left_0.png";  // 默认纹理
        }
        else
        {
            std::uniform_int_distribution<int> texDis(0, selectedType->textures.size() - 1);
            texturePath = selectedType->textures[texDis(gen)];
        }

        // 创建AI鱼并设置方向
        AIFish fish(renderer, texturePath, x, y, size, size);
        fish.setDirection((side == 0) ? 1 : -1);  // 左侧生成的鱼向右游，右侧生成的鱼向左游
        return fish;
    }

}  // namespace lx
