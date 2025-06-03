#ifndef FISH_H
#define FISH_H
#pragma once
#include "Renderer.h"
#include <SDL.h>
#include <string>

namespace lx {

    // 鱼类基类，定义鱼的基本属性和接口
    class Fish {
    public:
        // 构造函数，初始化鱼的位置、大小和纹理
        Fish(lyt::Renderer* renderer, const std::string& imagePath, int x, int y, int w, int h);
        // 析构函数，释放资源
        virtual ~Fish();

        // 更新鱼的状态，纯虚函数
        virtual void update(int windowW, int windowH) = 0;
        // 渲染鱼到屏幕
        virtual void render() const;
        // 判断鱼是否存活
        virtual bool isAlive() const { return alive; }
        // 让鱼变大
        virtual void grow(float scale);
        // 获取鱼的矩形区域
        virtual SDL_Rect getRect() const { return rect; }
        // 获取鱼的面积
        virtual float getSize() const { return rect.w * rect.h; }

    protected:
        lyt::Renderer* renderer; // 渲染器指针
        SDL_Texture* texture;    // 鱼的纹理
        SDL_Rect rect;           // 鱼的位置和大小
        bool alive = true;       // 鱼是否存活
    };

} // namespace lx

#endif
