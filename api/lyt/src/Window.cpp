/**
 * @file Window.cpp
 * @brief 窗口类实现，负责管理SDL窗口的创建、销毁和事件处理
 */

#include <Window.h>

namespace lyt
{
    /**
     * @brief 默认构造函数：创建一个空窗口对象
     */
    Window::Window() : width_(0), height_(0), event_() { window_ = nullptr; }

    /**
     * @brief 构造函数：使用已存在的SDL_Window指针创建窗口对象
     * @param window SDL_Window指针
     */
    Window::Window(SDL_Window* window) : width_(0), height_(0), event_() { window_ = window; }

    /**
     * @brief 构造函数：使用标题、宽度和高度创建一个新的窗口
     * @param title 窗口标题
     * @param width 窗口宽度
     * @param height 窗口高度
     * @throws std::runtime_error 如果窗口创建失败
     */
    Window::Window(const std::string& title, int width, int height) : width_(width), height_(height), event_()
    {
        // 创建SDL窗口，设置为居中显示、可见且可调整大小
        window_ = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);

        // 如果窗口创建失败，抛出运行时错误
        if (!window_)
        {
            throw std::runtime_error(SDL_GetError());
        }
    }

    /**
     * @brief 析构函数：清理窗口资源
     */
    Window::~Window()
    {
        if (window_)
        {
            SDL_DestroyWindow(window_);
        }
    }

    /**
     * @brief 处理窗口事件，特别是窗口大小调整事件
     * @param event SDL事件对象
     */
    void Window::handleEvents(SDL_Event& event)
    {
        // 当窗口被调整大小时更新窗口的宽度和高度
        if (event_.type == SDL_WINDOWEVENT && event_.window.event == SDL_WINDOWEVENT_RESIZED)
        {
            width_  = event_.window.data1;
            height_ = event_.window.data2;
        }
    }

    /**
     * @brief 设置窗口图标
     * @param filePath 图标文件路径
     */
    void Window::setIcon(const std::string& filePath) { SDL_SetWindowIcon(window_, IMG_Load(filePath.c_str())); }

    /**
     * @brief 获取窗口的大小
     * @param width 接收窗口宽度的引用
     * @param height 接收窗口高度的引用
     */
    void Window::getSize(int& width, int& height) const { SDL_GetWindowSize(window_, &width, &height); }

    /**
     * @brief 设置窗口全屏模式
     * @param fullScreen true为全屏，false为窗口模式
     */
    void Window::fullscreen(bool fullScreen)
    {
        if (fullScreen)
        {
            SDL_SetWindowFullscreen(window_, SDL_WINDOW_FULLSCREEN_DESKTOP);
        }
        else
        {
            SDL_SetWindowFullscreen(window_, 0);
        }
    }

    /**
     * @brief 隐藏或显示窗口
     * @param isHide true为隐藏，false为显示
     */
    void Window::hide(bool isHide)
    {
        if (isHide)
        {
            SDL_HideWindow(window_);
            flags &= SDL_WINDOW_SHOWN;
            flags |= SDL_WINDOW_HIDDEN;
        }
        else
        {
            SDL_ShowWindow(window_);
            flags &= SDL_WINDOW_HIDDEN;
            flags |= SDL_WINDOW_SHOWN;
        }
    }

    /**
     * @brief 设置窗口大小
     * @param width 窗口宽度
     * @param height 窗口高度
     */
    void Window::setSize(int width, int height) { SDL_SetWindowSize(window_, width, height); }
}  // namespace lyt
