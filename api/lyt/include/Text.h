﻿/**
 * @file Text.h
 * @brief 文本类头文件，负责处理文字的渲染和显示
 * @author restarhalf
 * @date 2025/5/29
 */

#ifndef TEXT_H
#define TEXT_H
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

#include "Renderer.h"

namespace lyt
{
    /**
     * @brief 文本类，负责处理文字的渲染和显示
     */
    class Text
    {
    private:
        SDL_Texture  *texture{nullptr};  ///< 文本纹理
        SDL_Rect      rect;  ///< 文本显示区域
        SDL_Color     color;  ///< 文本颜色
        TTF_Font     *font{nullptr};  ///< 字体
        SDL_Surface  *surface{nullptr};  ///< 文本表面
        SDL_BlendMode blendMode;  ///< 混合模式
        Uint8         alpha;  ///< 透明度
        std::string   text;  ///< 文本内容
        Renderer     *renderer{nullptr};  ///< 渲染器指针

    public:
        /**
         * @brief 默认构造函数
         */
        // 构造函数建议初始化所有成员变量，避免未定义行为
        Text();

        /**
         * @brief 析构函数，负责清理文本资源
         */
        ~Text();

        // Getters and setters
        [[nodiscard]] SDL_Texture  *getTexture() const;
        void                        setTexture(SDL_Texture *texture);
        [[nodiscard]] SDL_Rect      getRect() const;
        void                        setRect(const SDL_Rect &rect);
        [[nodiscard]] SDL_Color     getColor() const;
        void                        setColor(const SDL_Color &color);
        [[nodiscard]] TTF_Font     *getFont() const;
        void                        setFont(TTF_Font *font);
        [[nodiscard]] SDL_Surface  *getSurface() const;
        void                        setSurface(SDL_Surface *surface);
        [[nodiscard]] SDL_BlendMode getBlendmode() const;
        void                        setBlendmode(SDL_BlendMode BlendMode);
        [[nodiscard]] std::string   getText() const;
        void                        setText(const std::string &text);

        /**
         * @brief 设置文本的所有属性
         * @param render 渲染器指针
         * @param rect 文本显示区域
         * @param color 文本颜色
         * @param font 字体
         * @param blendMode 混合模式
         * @param text 文本内容
         */
        void setAll(Renderer *render, SDL_Rect rect, SDL_Color color, TTF_Font *font, SDL_BlendMode blendMode,
                    const std::string &text);

        /**
         * @brief 刷新文本纹理
         */
        void flush();

        /**
         * @brief 绘制文本
         */
        void draw();
        void setAlpha(Uint8 a)
        {
            if (texture) SDL_SetTextureAlphaMod(texture, a);
        }
        
    };
}  // namespace lyt

#endif  // TEXT_H
