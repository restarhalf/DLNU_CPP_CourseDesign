/**
 * @file Renderer.cpp
 * @brief 渲染器类实现，负责处理SDL渲染相关操作
 */
#include "../include/Renderer.h"
namespace lyt
{
    /**
     * @brief 使用现有的SDL_Renderer指针构造渲染器
     * @param renderer SDL_Renderer指针
     */
    Renderer::Renderer(SDL_Renderer* renderer) { renderer_ = renderer; }

    /**
     * @brief 默认构造函数，初始化渲染器指针为空
     */
    Renderer::Renderer() { renderer_ = nullptr; };

    /**
     * @brief 从窗口创建渲染器，可选择是否启用垂直同步
     * @param window 窗口指针
     * @param vsync 是否启用垂直同步
     * @throws std::runtime_error 如果渲染器创建失败
     */
    Renderer::Renderer(const Window* window, bool vsync)
    {
        // 设置渲染器标志
        Uint32 flags = SDL_RENDERER_ACCELERATED;  // 启用硬件加速
        if (vsync) flags |= SDL_RENDERER_PRESENTVSYNC;  // 如果需要，启用垂直同步

        // 创建渲染器
        renderer_ = SDL_CreateRenderer(const_cast<SDL_Window*>(window->get()), -1, flags);
        if (!renderer_)
        {
            throw std::runtime_error(SDL_GetError());
        }

        // 设置默认绘图颜色为白色
        SDL_SetRenderDrawColor(renderer_, 1000, 1000, 1000, 255);
    }

    /**
     * @brief 析构函数，清理渲染器资源
     */
    Renderer::~Renderer()
    {
        if (renderer_)
        {
            SDL_DestroyRenderer(renderer_);
            renderer_ = nullptr;
        }
    }

    /**
     * @brief 清除渲染目标
     */
    void Renderer::clear() { SDL_RenderClear(renderer_); }

    /**
     * @brief 将渲染内容呈现到屏幕
     */
    void Renderer::present() const { SDL_RenderPresent(renderer_); }

    /**
     * @brief 将纹理复制到渲染目标
     * @param texture 要复制的纹理
     * @param src 源矩形（可为nullptr表示整个纹理）
     * @param dst 目标矩形（可为nullptr表示整个渲染目标）
     * @param angle 旋转角度，默认为0.0
     * @param center 旋转中心点，默认为nullptr
     * @param flip 翻转标志，默认为SDL_FLIP_NONE
     * @return 成功返回0，失败返回负值
     */
    int Renderer::copy(SDL_Texture* texture, const SDL_Rect* src, const SDL_Rect* dst, double angle,
                       const SDL_Point* center, SDL_RendererFlip flip) const
    {
        return SDL_RenderCopyEx(renderer_, texture, src, dst, angle, center, flip);
    }

    /**
     * @brief 加载纹理
     * @param filePath 图像文件路径
     * @return SDL_Texture* 加载的纹理指针，加载失败返回nullptr
     */
    SDL_Texture* Renderer::loadTexture(const std::string& filePath) const
    {
        SDL_Texture* texture     = nullptr;
        SDL_Surface* tempSurface = IMG_Load(filePath.c_str());
        if (!tempSurface)
        {
            SDL_Log("Failed to load image %s, SDL_image Error: %s", filePath.c_str(), IMG_GetError());
            return nullptr;
        }
        texture = SDL_CreateTextureFromSurface(renderer_, tempSurface);
        SDL_FreeSurface(tempSurface);
        if (!texture)
        {
            SDL_Log("Failed to create texture from %s, SDL Error: %s", filePath.c_str(), SDL_GetError());
        }
        return texture;
    }

}  // namespace lyt
