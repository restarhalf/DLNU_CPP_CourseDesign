﻿/**
 * @file Controller.cpp
 * @brief 控制器类实现，负责处理键盘和鼠标的输入
 */

#include "Controller.h"

namespace lyt
{
    /**
     * @brief 默认构造函数
     */
    Controller::Controller()  = default;

    /**
     * @brief 析构函数
     */
    Controller::~Controller() = default;

    /**
     * @brief 处理所有输入事件
     * @param event SDL事件对象
     * @param x 鼠标X坐标引用
     * @param y 鼠标Y坐标引用
     */
    void Controller::event(SDL_Event& event, int& x, int& y)
    {
        switch (event.type)
        {
            case SDL_KEYDOWN:  // 键盘按下事件
                if (isKeytoMove) KeyboardPress(event, x, y);
                // 按下F1切换输入模式（鼠标/键盘）
                if (event.key.keysym.sym == SDLK_F1)
                {
                    isMousetoMove = !isMousetoMove;
                    isKeytoMove   = !isKeytoMove;
                    std::cout << "isMousetoMove:" << isMousetoMove << std::endl;
                }
                break;
            case SDL_KEYUP:  // 键盘释放事件
                KeyboardRelease(event, x, y);
                break;
            case SDL_MOUSEBUTTONDOWN:  // 鼠标按下事件
                MousePress(event);
                break;
            case SDL_MOUSEBUTTONUP:  // 鼠标释放事件
                MouseRelease(event);
                break;
            case SDL_MOUSEMOTION:  // 鼠标移动事件
                if (isMousetoMove) MouseMove(event, x, y);
                break;
            default:
                break;
        }
    }

    /**
     * @brief 处理键盘按下事件，更新坐标位置
     * @param event SDL事件对象
     * @param x 鼠标X坐标引用
     * @param y 鼠标Y坐标引用
     */
    void Controller::KeyboardPress(const SDL_Event& event, int& x, int& y)
    {
        keyStates[event.key.keysym.scancode] = true;
        switch (event.key.keysym.sym)
        {
            case SDLK_w:  // 向上移动
                SDL_Log("w");
                y--;
                break;
            case SDLK_s:  // 向下移动
                SDL_Log("s");
                y++;
                break;
            case SDLK_a:  // 向左移动
                SDL_Log("a");
                x--;
                break;
            case SDLK_d:  // 向右移动
                SDL_Log("d");
                x++;
                break;
            case SDLK_UP:  // 方向键上
                y--;
                break;
            case SDLK_LEFT:  // 方向键左
                x--;
                break;
            case SDLK_RIGHT:  // 方向键右
                x++;
                break;
            case SDLK_DOWN:  // 方向键下
                y++;
                break;
            case SDLK_SPACE:  // 空格键
                break;
            default:
                break;
        }
    }

    /**
     * @brief 处理键盘释放事件
     * @param event SDL事件对象
     * @param x 鼠标X坐标引用
     * @param y 鼠标Y坐标引用
     */
    void Controller::KeyboardRelease(const SDL_Event& event, int& x, int& y)
    {
        keyStates[event.key.keysym.scancode] = false;
        switch (event.key.keysym.sym)
        {
            case SDLK_w:
                y--;
                break;
            case SDLK_s:
                y++;
                break;
            case SDLK_a:
                x--;
                break;
            case SDLK_d:
                x++;
                break;
            case SDLK_UP:
                y--;
                break;
            case SDLK_LEFT:
                x--;
                break;
            case SDLK_RIGHT:
                x++;
                break;
            case SDLK_DOWN:
                y++;
                break;
            case SDLK_SPACE:
                break;
            default:
                break;
        }
    }

    /**
     * @brief 处理鼠标按键事件
     * @param event SDL事件对象
     */
    void Controller::MousePress(const SDL_Event& event)
    {
        switch (event.button.button)
        {
            case SDL_BUTTON_LEFT:  // 左键
                break;
            case SDL_BUTTON_RIGHT:  // 右键
                break;
            case SDL_BUTTON_MIDDLE:  // 中键
                break;
            default:
                break;
        }
    }

    /**
     * @brief 处理鼠标释放事件
     * @param event SDL事件对象
     */
    void Controller::MouseRelease(const SDL_Event& event)
    {
        switch (event.button.button)
        {
            case SDL_BUTTON_LEFT:  // 左键释放
                break;
            case SDL_BUTTON_RIGHT:  // 右键释放
                break;
            case SDL_BUTTON_MIDDLE:  // 中键释放
                break;
            default:
                break;
        }
    }

    /**
     * @brief 处理鼠标移动事件，更新鼠标坐标
     * @param event SDL事件对象
     * @param x 鼠标X坐标引用
     * @param y 鼠标Y坐标引用
     */
    void Controller::MouseMove(const SDL_Event& event, int& x, int& y)
    {
        x = event.motion.x;
        y = event.motion.y;
    }

    /**
     * @brief 检查指定扫描码对应的按键是否被按下
     * @param scancode SDL键盘扫描码
     * @return 如果按下则返回true
     */
    bool Controller::isKeyPressed(SDL_Scancode scancode) const
    {
        auto it = keyStates.find(scancode);
        return it != keyStates.end() && it->second;
    }
    void Controller::reset()
    {
        keyStates.clear();
    }
}  // namespace lyt
