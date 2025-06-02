#include "../include/Renderer.h"
namespace lyt
{
    // 使用现有的SDL_Renderer指针构造渲染器
    Renderer::Renderer(SDL_Renderer* renderer) { renderer_ = renderer; }

    // 默认构造函数，初始化渲染器指针为空
    Renderer::Renderer() { renderer_ = nullptr; };

    // 从窗口创建渲染器，可选择是否启用垂直同步
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

    // 析构函数，清理渲染器资源
    Renderer::~Renderer()
    {
        if (renderer_)
        {
            SDL_DestroyRenderer(renderer_);
        }
    }

    // 清除渲染目标
    void Renderer::clear() const { SDL_RenderClear(renderer_); }

    // 将渲染内容呈现到屏幕
    void Renderer::present() const { SDL_RenderPresent(renderer_); }

    // 将纹理复制到渲染目标
    int Renderer::copy(SDL_Texture* texture, const SDL_Rect* src, const SDL_Rect* dst) const
    {
        return SDL_RenderCopy(renderer_, texture, src, dst);
    }
    // Renderer.cpp 内新增
    SDL_Texture* Renderer::loadTexture(const std::string& filePath) const
    {
        SDL_Texture* texture = nullptr;
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