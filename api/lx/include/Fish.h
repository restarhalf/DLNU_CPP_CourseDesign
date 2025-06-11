#ifndef FISH_H
#define FISH_H
#pragma once
#include "Renderer.h"
#include <SDL.h>
#include <string>
#include <cmath>
#include<vector>
#include <unordered_map>

namespace lx {

    /**
     * @brief 鱼类基类，定义鱼的基本属性和接口
     */
    class Fish {
    public:
        /**
         * @brief 构造函数，初始化鱼的位置、大小和纹理
         * @param renderer 渲染器指针
         * @param imagePath 鱼的图像路径
         * @param x X坐标
         * @param y Y坐标
         * @param w 宽度
         * @param h 高度
         */
        Fish(lyt::Renderer* renderer, const std::string& imagePath, int x, int y, int w, int h);

        /**
         * @brief 析构函数，释放资源
         */
        virtual ~Fish();

        /**
         * @brief 更新鱼的状态，纯虚函数
         * @param windowW 窗口宽度
         * @param windowH 窗口高度
         */
        virtual void update(int windowW, int windowH) = 0;

        /**
         * @brief 渲染鱼到屏幕
         */
        virtual void render() const;

        /**
         * @brief 判断鱼是否存活
         * @return 鱼是否存活
         */
        virtual bool isAlive() const { return alive; }

        /**
         * @brief 让鱼变大
         * @param scale 增长比例
         */
        virtual void grow(float scale);

        /**
         * @brief 获取鱼的矩形区域
         * @return 鱼的矩形区域
         */
        virtual SDL_Rect getRect() const { return rect; }

        /**
         * @brief 获取鱼的面积
         * @return 鱼的面积
         */
        virtual float getSize() const { return rect.w * rect.h; }

        /**
         * @brief 杀死鱼，将alive设为false
         */
        void kill() { alive = false; }

        /**
         * @brief 清理所有缓存的纹理
         */
        static void clearTextureCache();

        /**
         * @brief 获取或加载纹理
         * @param imagePath 图像路径
         * @return 加载的纹理
         */
        SDL_Texture* getOrLoadTexture(const std::string& imagePath);
    protected:
        lyt::Renderer* renderer; ///< 渲染器指针
        SDL_Texture* texture;    ///< 鱼的纹理
        int direction = 1;       ///< 方向，-1为左，1为右
        SDL_Rect rect;           ///< 鱼的位置和大小
        bool alive = true;       ///< 鱼是否存活
        static std::unordered_map<std::string, SDL_Texture*> textureCache;

    };

} // namespace lx

#endif
