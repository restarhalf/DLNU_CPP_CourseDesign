#include "Fish.h"

namespace lx {

    // 构造函数，加载鱼的纹理并初始化位置和尺寸
    Fish::Fish(lyt::Renderer* renderer, const std::string& imagePath, int x, int y, int w, int h)
        : renderer(renderer), rect{ x, y, w, h } {
        texture = renderer->loadTexture(imagePath);
        if (!texture) SDL_Log("Failed to load fish texture: %s", imagePath.c_str());
    }

    // 析构函数，释放纹理资源
    Fish::~Fish() {
        if (texture) SDL_DestroyTexture(texture);
    }

    // 渲染鱼到屏幕
    void Fish::render() const {
        renderer->copy(texture, nullptr, &rect);
    }

    // 让鱼变大，按比例缩放宽高
    void Fish::grow(float scale) {
        rect.w = static_cast<int>(rect.w * scale);
        rect.h = static_cast<int>(rect.h * scale);
    }

} // namespace lx
