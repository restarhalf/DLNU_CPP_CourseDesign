/**
 * @file Text.cpp
 * @brief 文本类实现，负责处理文字的渲染和显示
 */

#include "Text.h"

namespace lyt
{
    Text::Text() :
        texture(nullptr), rect{0, 0, 0, 0}, color{0, 0, 0, 255}, font(nullptr), surface(nullptr),
        blendMode(SDL_BLENDMODE_BLEND), alpha(255), text(""), renderer(nullptr)
    {}
    
    /**
     * @brief 析构函数，按顺序清理资源
     */
    Text::~Text()
    {
        // 按顺序释放资源：纹理、表面、字体
        if (texture) SDL_DestroyTexture(texture);
        if (surface) SDL_FreeSurface(surface);
        if (font) TTF_CloseFont(font);
        texture = nullptr;
        surface = nullptr;
        font    = nullptr;
    }

    // Getters and setters 实现
    /**
     * @brief 获取文本纹理
     * @return SDL_Texture* 纹理指针
     */
    SDL_Texture* Text::getTexture() const { return texture; }

    /**
     * @brief 设置文本纹理
     * @param texture 新的纹理指针
     */
    void Text::setTexture(SDL_Texture* const texture) { this->texture = texture; }

    /**
     * @brief 获取文本矩形区域
     * @return SDL_Rect 矩形区域
     */
    SDL_Rect Text::getRect() const { return rect; }

    /**
     * @brief 设置文本矩形区域
     * @param rect 新的矩形区域
     */
    void Text::setRect(const SDL_Rect &rect) { this->rect = rect; }

    /**
     * @brief 获取文本颜色
     * @return SDL_Color 文本颜色
     */
    SDL_Color Text::getColor() const { return color; }

    /**
     * @brief 设置文本颜色
     * @param color 新的文本颜色
     */
  
    void Text::setColor(const SDL_Color& color)
    {
        SDL_SetTextureColorMod(texture, color.r, color.g, color.b);  // 修改纹理颜色
        SDL_SetTextureAlphaMod(texture, color.a);  // 修改透明度（可选）
    }

    /**
     * @brief 获取文本使用的字体
     * @return TTF_Font* 字体指针
     */
    TTF_Font* Text::getFont() const { return font; }

    /**
     * @brief 设置文本使用的字体
     * @param font 新的字体指针
     */
    void Text::setFont(TTF_Font* const font) { this->font = font; }

    /**
     * @brief 获取文本表面
     * @return SDL_Surface* 表面指针
     */
    SDL_Surface* Text::getSurface() const { return surface; }

    /**
     * @brief 设置文本表面
     * @param surface 新的表面指针
     */
    void Text::setSurface(SDL_Surface* const surface) { this->surface = surface; }

    /**
     * @brief 获取文本混合模式
     * @return SDL_BlendMode 混合模式
     */
    SDL_BlendMode Text::getBlendmode() const { return blendMode; }

    /**
     * @brief 设置文本混合模式
     * @param blend_mode 新的混合模式
     */
    void Text::setBlendmode(const SDL_BlendMode blend_mode) { blendMode = blend_mode; }

    /**
     * @brief 获取文本内容
     * @return std::string 文本内容
     */
    std::string Text::getText() const { return text; }

    /**
     * @brief 设置文本内容
     * @param text 新的文本内容
     */
    void Text::setText(const std::string &text)
    {
        if (this->text != text)
        {
            this->text = text;
             flush();
        }
    }
    

    /**
     * @brief 设置文本的所有属性并创建纹理
     * @param render 渲染器指针
     * @param rect 文本显示区域
     * @param color 文本颜色
     * @param font 字体指针
     * @param blendMode 混合模式
     * @param text 文本内容
     */
    void Text::setAll(Renderer *render, SDL_Rect rect, SDL_Color color, TTF_Font *font, SDL_BlendMode blendMode,
                      const std::string &text)
    {
        if (text==this->text) return;
        // 设置基本属性
        this->rect      = rect;
        this->color     = color;
        this->font      = font;
        this->blendMode = blendMode;
        this->text      = text;
        this->renderer  = render;

        // 清理旧的纹理（如果存在）
        if (texture) SDL_DestroyTexture(texture);

        // 使用字体渲染文本
        surface = TTF_RenderUTF8_Blended(this->font, this->text.c_str(), this->color);
        if (!surface)
        {
            SDL_Log("Failed to create surface: %s", SDL_GetError());
            return;
        }

        // 从表面创建纹理
        texture = SDL_CreateTextureFromSurface(render->get(), surface);
        SDL_SetTextureBlendMode(texture, this->blendMode);
        if (!texture)
        {
            SDL_Log("Failed to create texture: %s", SDL_GetError());
            SDL_FreeSurface(surface);
        }
    }

    /**
     * @brief 刷新文本纹理，重新渲染当前文本
     */
    void Text::flush()
    {
        // 检查 renderer 和 font 是否有效
        if (!renderer || !renderer->get())
        {
            SDL_Log("flush() failed: renderer is null");
            return;
        }
        if (!font)
        {
            SDL_Log("flush() failed: font is null");
            return;
        }

        // 清理旧资源
        if (texture)
        {
            SDL_DestroyTexture(texture);
            texture = nullptr;
        }
        if (surface)
        {
            SDL_FreeSurface(surface);
            surface = nullptr;
        }

        // 创建新 surface
        surface = TTF_RenderUTF8_Blended(font, text.c_str(), color);
        if (!surface)
        {
            SDL_Log("flush() failed: TTF_RenderUTF8_Blended: %s", TTF_GetError());
            return;
        }

        // 创建新 texture
        texture = SDL_CreateTextureFromSurface(renderer->get(), surface);
        if (!texture)
        {
            SDL_Log("flush() failed: SDL_CreateTextureFromSurface: %s", SDL_GetError());
            SDL_FreeSurface(surface);
            surface = nullptr;
            return;
        }

        // 设置混合模式和透明度
        SDL_SetTextureBlendMode(texture, blendMode);
        SDL_SetTextureAlphaMod(texture, alpha);

        //SDL_Log("flush() success: text='%s'", text.c_str());
    }

    


    /**
     * @brief 绘制文本到屏幕
     */
    void Text::draw()
    {
        renderer->copy(texture, nullptr, &rect);
        //SDL_Log("flush alpha = %d", alpha);
    }

}  // namespace lyt
