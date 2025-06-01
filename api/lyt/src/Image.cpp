#include "Image.h"
namespace lyt
{
    Image::Image() {}

    Image::~Image()
    {
        if (texture) SDL_DestroyTexture(texture);
        IMG_Quit();
    }

    void Image::draw()
    {
        this->renderer->copy(texture, nullptr, &rect);
        SDL_FreeSurface(surface);
    }

    void Image::setImage(const std::string& filePath, Renderer* renderer, SDL_Rect rect, SDL_BlendMode blendMode,
                         Uint8 alpha)
    {
        this->rect      = rect;
        this->blendMode = blendMode;
        this->alpha     = alpha;
        this->filePath  = filePath;
        this->renderer  = renderer;
        surface         = IMG_Load(filePath.c_str());
        if (surface == nullptr)
        {
            throw std::runtime_error("Failed to load image: " + std::string(SDL_GetError()));
        }
        if (texture) SDL_DestroyTexture(texture);
        texture = SDL_CreateTextureFromSurface(renderer->get(), surface);
        if (!texture)
        {
            throw std::runtime_error(SDL_GetError());
        }
        SDL_SetTextureBlendMode(texture, blendMode);
        SDL_SetTextureAlphaMod(texture, alpha);
    }
    SDL_Rect      Image::getRect() const { return rect; }
    void          Image::setRect(const SDL_Rect& rect) { this->rect = rect; }
    SDL_Color     Image::getColor() const { return color; }
    void          Image::setColor(const SDL_Color& color) { this->color = color; }
    std::string   Image::getFilepath() const { return filePath; }
    void          Image::setFilepath(const std::string& file_path) { filePath = file_path; }
    Renderer*     Image::getRenderer() const { return renderer; }
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
