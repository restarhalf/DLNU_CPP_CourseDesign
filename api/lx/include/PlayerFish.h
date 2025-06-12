#pragma once
#include "AIFish.h"
#include "Controller.h"
#include "Fish.h"
#include "ScoreManager.h"


namespace lx
{

    /**
     * @brief 玩家控制的鱼类，继承自Fish
     */
    class PlayerFish : public Fish
    {
    public:
        /**
         * @brief 构造函数，初始化玩家鱼的位置和图片
         * @param renderer 渲染器指针
         * @param imagePath 图片路径
         * @param x 初始x坐标
         * @param y 初始y坐标
         * @param w 宽度
         * @param h 高度
         */
        PlayerFish(lyt::Renderer* renderer, const std::string& imagePath, int x, int y, int w, int h);

        /**
         * @brief 更新玩家鱼的位置和状态
         * @param windowW 窗口宽度
         * @param windowH 窗口高度
         */
        void update(int windowW, int windowH) override;

        /**
         * @brief 处理输入控制（键盘或鼠标）
         * @param controller 控制器指针
         */
        void handleInput(const lyt::Controller* controller);

        /**
         * @brief 尝试吃掉AI鱼，成功则加分
         * @param ai AI鱼对象引用
         * @param scoreManager 分数管理器引用
         * @return 是否成功吃掉AI鱼
         */
        bool tryEat(AIFish& ai, ScoreManager& scoreManager);

        /**
         * @brief 重置玩家鱼的位置
         * @param startX 起始X坐标
         * @param startY 起始Y坐标
         */
        void reset(int startX, int startY,lyt::Controller* controller);

        /**
         * @brief 调整玩家鱼大小至最大值
         */
        void resize();

        /**
         * @brief 获取鱼的移动方向
         * @return 移动方向（1为右，-1为左）
         */
        int getDirection() const { return direction; }

        /**
         * @brief 设置鱼的移动方向
         * @param dir 移动方向
         */
        void setDirection(int dir) { direction = dir; }

        /**
         * @brief 获取鱼的图片路径
         * @return 图片路径
         */
        std::string getImagePath() { return imagePath; }

        /**
         * @brief 设置鱼的图片路径
         * @param path 新的图片路径
         */
        void setImagePath(const std::string& path) { imagePath = path; }
        

    private:
        int velocityX = 0;  ///< X方向速度
        int velocityY = 0;  ///< Y方向速度
        int speed     = 4;  ///< 移动速度
        int wMax      = 150; ///< 最大宽度
        std::string imagePath;  ///< 鱼的图片路径
    };

}  // namespace lx
