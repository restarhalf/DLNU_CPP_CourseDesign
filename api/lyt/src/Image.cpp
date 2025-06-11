/**
 * @file Image.cpp
 * @brief 图像类实现，负责处理图片资源的加载、显示和管理
 */

#include "Image.h"
namespace lyt
{
    /**
     * @brief 默认构造函数
     */
    Image::Image() : rect(), color(), renderer(nullptr) {}

    /**
     * @brief 析构函数：清理图像资源
     */
    Image::~Image()
    {
        if (texture) SDL_DestroyTexture(texture);
        if (surface) SDL_FreeSurface(surface);
    }

    /**
     * @brief 绘制图像
     */
    void Image::draw() { this->renderer->copy(texture, nullptr, &rect); }

    /**
     * @brief 设置图像的所有属性并加载图像
     * @param filePath 图像文件路径
     * @param renderer 渲染器指针
     * @param rect 图像显示区域
     * @param blendMode 混合模式
     * @param alpha 透明度
     * @throws std::runtime_error 如果图像加载失败
     */
    void Image::setImage(const std::string& filePath, Renderer* renderer, SDL_Rect rect, SDL_BlendMode blendMode,
                         Uint8 alpha)
    {
        this->rect      = rect;
        this->blendMode = blendMode;
        this->alpha     = alpha;
        this->filePath  = filePath;
        this->renderer  = renderer;

        // 加载图像表面
        surface = IMG_Load(this->filePath.c_str());
        if (surface == nullptr)
        {
            throw std::runtime_error("Failed to load image: " + std::string(SDL_GetError()));
        }

        // 清理旧的纹理并创建新的纹理
        if (texture) SDL_DestroyTexture(texture);
        texture = SDL_CreateTextureFromSurface(renderer->get(), surface);
        if (!texture)
        {
            throw std::runtime_error(SDL_GetError());
        }

        // 设置纹理的混合模式和透明度
        SDL_SetTextureBlendMode(texture, blendMode);
        SDL_SetTextureAlphaMod(texture, alpha);
    }

    // Getters and setters
    /**
     * @brief 获取图像矩形区域
     * @return 图像显示的矩形区域
     */
    SDL_Rect Image::getRect() const { return rect; }

    /**
     * @brief 设置图像矩形区域
     * @param rect 新的矩形区域
     */
    void Image::setRect(const SDL_Rect& rect) { this->rect = rect; }

    /**
     * @brief 获取图像颜色
     * @return 图像的颜色
     */
    SDL_Color Image::getColor() const { return color; }

    /**
     * @brief 设置图像颜色
     * @param color 新的颜色
     */
    void Image::setColor(const SDL_Color& color) { this->color = color; }

    /**
     * @brief 获取图像文件路径
     * @return 文件路径
     */
    std::string Image::getFilepath() const { return filePath; }

    /**
     * @brief 设置图像文件路径
     * @param file_path 新的文件路径
     */
    void Image::setFilepath(const std::string& file_path) { filePath = file_path; }

    /**
     * @brief 获取渲染器指针
     * @return 渲染器指针
     */
    Renderer* Image::getRenderer() const { return renderer; }

    /**
     * @brief 设置渲染器指针
     * @param renderer 新的渲染器指针
     */
    void Image::setRenderer(Renderer* renderer) { this->renderer = renderer; }

    /**
     * @brief 获取混合模式
     * @return 当前的混合模式
     */
    SDL_BlendMode Image::getBlendmode() const { return blendMode; }

    /**
     * @brief 设置混合模式
     * @param blend_mode 新的混合模式
     */
    void Image::setBlendmode(SDL_BlendMode blend_mode)
    {
        blendMode = blend_mode;
        SDL_SetTextureBlendMode(texture, this->blendMode);
    }

    /**
     * @brief 获取透明度
     * @return 当前透明度
     */
    Uint8 Image::getAlpha() const { return alpha; }

    /**
     * @brief 设置透明度
     * @param alpha 新的透明度值
     */
    void Image::setAlpha(Uint8 alpha)
    {
        this->alpha = alpha;
        SDL_SetTextureAlphaMod(texture, this->alpha);
    }
}  // namespace lyt
