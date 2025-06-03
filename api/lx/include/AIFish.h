    #ifndef AIFISH_H
    #define AIFISH_H

    #pragma once
    #include "Fish.h"

    namespace lx {

        /**
         * @brief AI鱼类，继承自Fish，具备自动移动和成长等行为
         */
        class AIFish : public Fish {
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

            /**
             * @brief 更新AI鱼的位置和状态
             * @param windowW 窗口宽度
             * @param windowH 窗口高度
             */
            void update(int windowW, int windowH) override;

            /**
             * @brief 杀死鱼，将alive设为false
             */
            void kill() { alive = false; }

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

        private:
            int speed;      ///< 移动速度
            int direction;  ///< 移动方向，-1为左，1为右
            int scoreValue; ///< 分值
        };

    } // namespace lx

    #endif
