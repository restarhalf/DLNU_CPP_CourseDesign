#pragma once
//
// Created by restarhalf on 2025/5/29.
//

#ifndef RENDERER_H
#define RENDERER_H
#include <SDL.h>

#include "Window.h"

namespace lyt
{
    /**
     * @brief 渲染器类，负责处理SDL渲染相关操作
     */
    class Renderer
    {
    public:
        /**
         * @brief 默认构造函数，创建一个空的渲染器对象
         */
        Renderer();

        /**
         * @brief 使用已存在的SDL_Renderer指针构造渲染器对象
         * @param renderer SDL_Renderer指针
         */
        explicit Renderer(SDL_Renderer* renderer);

        /**
         * @brief 从窗口创建渲染器
         * @param window 窗口对象指针
         * @param vsync 是否启用垂直同步
         */
        explicit Renderer(const Window* window, bool vsync);

        /**
         * @brief 析构函数，负责清理渲染器资源
         */
        ~Renderer();

        /**
         * @brief 清除渲染目标
         */
        void clear();

        /**
         * @brief 将渲染内容呈现到屏幕
         */
        void present() const;

        /**
         * @brief 将纹理复制到渲染目标
         * @param texture 要复制的纹理
         * @param src 源矩形（可为nullptr表示整个纹理）
         * @param dst 目标矩形（可为nullptr表示整个渲染目标）
         * @return 成功返回0，失败返回负值
         */
        int copy(SDL_Texture* texture, const SDL_Rect* src, const SDL_Rect* dst) const;


        /**
         * @brief 获取SDL_Renderer指针
         * @return SDL_Renderer指针
         */
        [[nodiscard]] SDL_Renderer* get() const { return renderer_; }
        SDL_Texture*                loadTexture(const std::string& filePath) const;

    private:
        SDL_Renderer* renderer_ = nullptr;  ///< SDL渲染器指针
        // Renderer.h 内新增
    };
}  // namespace lyt

#endif  // RENDERER_H
