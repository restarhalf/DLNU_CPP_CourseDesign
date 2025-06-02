#include "Image.h"
namespace lyt
{
    // 默认构造函数
    Image::Image() : rect(), color(), renderer(nullptr) {}

    // 析构函数：清理图像资源
    Image::~Image()
    {
        if (texture) SDL_DestroyTexture(texture);
        if (surface) SDL_FreeSurface(surface);
    }

    // 绘制图像
    void Image::draw() { this->renderer->copy(texture, nullptr, &rect); }

    // 设置图像的所有属性并加载图像
    void Image::setImage(const std::string& filePath, Renderer* renderer, SDL_Rect rect, SDL_BlendMode blendMode,
        Uint8 alpha)
    {
        this->rect = rect;
        this->blendMode = blendMode;
        this->alpha = alpha;
        this->filePath = filePath;
        this->renderer = renderer;

        // 加载图像表面
        surface = IMG_Load(filePath.c_str());
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
    SDL_Rect      Image::getRect() const { return rect; }
    void          Image::setRect(const SDL_Rect& rect) { this->rect = rect; }
    SDL_Color     Image::getColor() const { return color; }
    void          Image::setColor(const SDL_Color& color) { this->color = color; }
    std::string   Image::getFilepath() const { return filePath; }
    void          Image::setFilepath(const std::string& file_path) { filePath = file_path; }
    Renderer* Image::getRenderer() const { return renderer; }
    void          Image::setRenderer(Renderer* renderer) { this->renderer = renderer; }
    SDL_BlendMode Image::getBlendmode() const { return blendMode; }
    void          Image::setBlendmode(SDL_BlendMode blend_mode)
    {
        blendMode = blend_mode;
        SDL_SetTextureBlendMode(texture, blend_mode);
    }
    Uint8 Image::getAlpha() const { return alpha; }
    void  Image::setAlpha(Uint8 alpha)
    {
        this->alpha = alpha;
        SDL_SetTextureAlphaMod(texture, alpha);
    }
}  // namespace lyt