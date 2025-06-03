#pragma once
#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <SDL.h>
#include <bits/stdc++.h>

namespace lyt
{
    /**
     * @brief 控制器类，负责处理键盘和鼠标的输入控制
     */
    class Controller
    {
    public:
        /**
         * @brief 默认构造函数
         */
        Controller();

        /**
         * @brief 析构函数
         */
        ~Controller();

        /**
         * @brief 处理输入事件
         * @param event SDL事件对象
         * @param x 鼠标x坐标引用
         * @param y 鼠标y坐标引用
         */
        void event(SDL_Event& event, int& x, int& y);

        /**
         * @brief 处理键盘按下事件
         * @param event SDL事件对象
         * @param x 坐标x引用
         * @param y 坐标y引用
         */
        void KeyboardPress(const SDL_Event& event, int& x, int& y);

        /**
         * @brief 处理键盘释放事件
         * @param event SDL事件对象
         * @param x 坐标x引用
         * @param y 坐标y引用
         */
        void KeyboardRelease(const SDL_Event& event, int& x, int& y);

        /**
         * @brief 处理鼠标按下事件
         * @param event SDL事件对象
         */
        void MousePress(const SDL_Event& event);

        /**
         * @brief 处理鼠标释放事件
         * @param event SDL事件对象
         */
        void MouseRelease(const SDL_Event& event);

        /**
         * @brief 处理鼠标移动事件
         * @param event SDL事件对象
         * @param x 鼠标x坐标引用
         * @param y 鼠标y坐标引用
         */
        void MouseMove(const SDL_Event& event, int& x, int& y);

        /**
         * @brief 查询指定按键是否被按下
         * @param scancode SDL键盘扫描码
         * @return 如果按下则返回true
         */
        bool isKeyPressed(SDL_Scancode scancode) const;

    private:
        bool isMousetoMove = false;  ///< 是否启用鼠标移动控制
        bool isKeytoMove = true;  ///< 是否启用键盘移动控制
        std::unordered_map<SDL_Scancode, bool> keyStates;//记录各个键盘按键当前的状态（按下为 true，未按下为 false）

    };
}  // namespace lyt

#endif  // CONTROLLER_H
