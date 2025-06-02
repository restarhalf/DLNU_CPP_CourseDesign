#pragma once

#ifndef WINDOW_H
#define WINDOW_H
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <bits/stdc++.h>

namespace lyt
{
    /**
     * @brief 窗口类，负责管理SDL窗口的创建、销毁和事件处理
     */
    class Window
    {
    public:
        /**
         * @brief 默认构造函数，创建一个空的窗口对象
         */
        Window();

        /**
         * @brief 使用已存在的SDL_Window指针构造窗口对象
         * @param window SDL_Window指针
         */
        Window(SDL_Window* window);

        /**
         * @brief 使用指定的标题、宽度和高度创建窗口
         * @param title 窗口标题
         * @param width 窗口宽度
         * @param height 窗口高度
         */
        Window(const std::string& title, int width, int height);

        /**
         * @brief 析构函数，负责清理窗口资源
         */
        ~Window();

        /**
         * @brief 处理窗口相关的SDL事件
         * @param event SDL事件对象
         */
        void handleEvents(SDL_Event& event);

        /**
         * @brief 获取SDL_Window指针
         * @return SDL_Window指针
         */
        SDL_Window* get() const { return window_; }

        /**
         * @brief 获取窗口宽度
         * @return 窗口宽度
         */
        int width() const { return width_; }

        /**
         * @brief 获取窗口高度
         * @return 窗口高度
         */
        int height() const { return height_; }
        /**
         * @brief 设置图标
         * @param filePath 图标文件路径
         */
        void setIcon(const std::string& filePath);
        /**
         * @brief 获取尺寸
         * @param width 窗口宽度
         * @param height 窗口高度
         */
        void getSize(int& width, int& height) const;
        /**
         * @brief 设置窗口全屏
         * @param fullScreen 是否全屏
         */
        void fullscreen(bool fullScreen);
        /**
         * @brief 设置窗口隐藏
         * @param isHide 是否隐藏
         */
        void hide(bool isHide);

    private:
        SDL_Window* window_ = nullptr;  ///< SDL窗口指针
        int         width_;  ///< 窗口宽度
        int         height_;  ///< 窗口高度
        SDL_Event   event_;  ///< SDL事件对象
        Uint32      flags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN;  ///< 窗口标志，默认可调整大小且可见
    };
}  // namespace lyt
#endif  // WINDOW_H