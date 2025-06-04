#include <Window.h>

namespace lyt
{
    // 默认构造函数：创建一个空窗口对象
    Window::Window() : width_(0), height_(0), event_() { window_ = nullptr; }

    // 构造函数：使用已存在的SDL_Window指针创建窗口对象
    Window::Window(SDL_Window* window) : width_(0), height_(0), event_() { window_ = window; }

    // 构造函数：使用标题、宽度和高度创建一个新的窗口
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

    // 析构函数：清理窗口资源
    Window::~Window()
    {
        if (window_)
        {
            SDL_DestroyWindow(window_);
        }
    }

    // 处理窗口事件，特别是窗口大小调整事件
    void Window::handleEvents(SDL_Event& event)
    {
        // 当窗口被调整大小时更新窗口的宽度和高度
        if (event_.type == SDL_WINDOWEVENT && event_.window.event == SDL_WINDOWEVENT_RESIZED)
        {
            width_  = event_.window.data1;
            height_ = event_.window.data2;
        }
    }
    // 设置窗口图标
    void Window::setIcon(const std::string& filePath) { SDL_SetWindowIcon(window_, IMG_Load(filePath.c_str())); }
    // 获取窗口的大小
    void Window::getSize(int& width, int& height) const { SDL_GetWindowSize(window_, &width, &height); }
    // 设置全屏
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
    // 隐藏窗口
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
    void Window::setSize(int width, int height) { SDL_SetWindowSize(window_, width, height); }
}  // namespace lyt
