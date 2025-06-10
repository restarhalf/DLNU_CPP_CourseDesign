#include "Fish.h"

namespace lx {

std::unordered_map<std::string, SDL_Texture*> Fish::textureCache;

// 构造函数，加载鱼的纹理并初始化位置和尺寸
Fish::Fish(lyt::Renderer* renderer, const std::string& imagePath, int x, int y, int w, int h) :
    renderer(renderer), rect{x, y, w, h}
{
    texture = getOrLoadTexture(imagePath);
}

// 纹理缓存机制
SDL_Texture* Fish::getOrLoadTexture(const std::string& imagePath) {
    auto it = textureCache.find(imagePath);
    if (it != textureCache.end()) {
        return it->second;
    }

    SDL_Texture* newTexture = renderer->loadTexture(imagePath);
    if (!newTexture) {
        std::string error = "Failed to load fish texture: " + imagePath + " SDL Error: " + SDL_GetError();
        SDL_Log("%s", error.c_str());
        throw std::runtime_error(error);
    }

    textureCache[imagePath] = newTexture;
    return newTexture;
}

// 清除纹理缓存
void Fish::clearTextureCache() {
    for (auto& [path, texture] : textureCache) {
        if (texture) {
            SDL_DestroyTexture(texture);
        }
    }
    textureCache.clear();
}

// 析构函数，释放纹理资源
Fish::~Fish() {
    // 不在这里释放texture，因为它现在由缓存管理
}

// 渲染鱼到屏幕
void Fish::render() const
{
    SDL_RendererFlip flip = (direction == -1) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    renderer->copy(texture, nullptr, &rect, 0.0, nullptr, flip);
    SDL_Log("Fish direction: %d", direction);
}


// 让鱼变大，按比例缩放宽高
void Fish::grow(float scale)
{
    rect.w = static_cast<int>(rect.w * scale);
    rect.h = static_cast<int>(rect.h * scale);
}

}  // namespace lx
