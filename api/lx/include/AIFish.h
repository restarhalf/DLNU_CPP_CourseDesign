#ifndef AIFISH_H
#define AIFISH_H

#pragma once
#include <random>
#include <vector>

#include "Fish.h"

namespace lx
{
    /**
     * @brief 鱼类类型定义，描述不同体积范围对应的纹理
     */
    struct FishType
    {
        int                      minSize;  ///< 最小体积
        int                      maxSize;  ///< 最大体积
        std::vector<std::string> textures;  ///< 向左游的纹理路径集合
    };

    /**
     * @brief AI鱼类，继承自Fish，具备自动移动和成长等行为
     */
    class AIFish : public Fish
    {
    public:
        /**
         * @brief 构造函数，初始化AI鱼对象
         * @param renderer 渲染器指针
         * @param imagePath 图片路径
         * @param x 初始x坐标
         * @param y 初始y坐标
         * @param w 宽度
         * @param h 高度
         */
        AIFish(lyt::Renderer* renderer, const std::string& imagePath, int x, int y, int w, int h);


        static AIFish createRandomFish(lyt::Renderer* renderer, const std::vector<FishType>& fishTypes, int windowW,
                                       int windowH, std::mt19937& gen,
                                       int playerSize  // 玩家鱼体积参考
        );
        /**
         * @brief 更新AI鱼的位置和状态
         * @param windowW 窗口宽度
         * @param windowH 窗口高度
         */
        void update(int windowW, int windowH) override;
        /**
         * @brief 设置AI鱼移动方向
         * @param dir 鱼的方向
         */
        void setDirection(int dir);
        int  getDirection() const;
        /**
         * @brief 让鱼成长，变大
         * @param scale 成长比例
         */
        void grow(float scale) override;

        /**
         * @brief 获取鱼的分值
         * @return 分值
         */
        int getScoreValue() const;
        /**
         * @brief 获取鱼的特殊分值
         * @return 特殊分值
         */
        int getspecialValue() const;
        // static std::vector<FishType> FishTypes;  //实现依据体积随机赋予纹理


    private:
        int speed;  ///< 移动速度
        // int direction;  ///< 移动方向，-1为左，1为右
        int scoreValue;  ///< 分值
        int specialValue;  ///< 特殊分值
    };

}  // namespace lx

#endif
