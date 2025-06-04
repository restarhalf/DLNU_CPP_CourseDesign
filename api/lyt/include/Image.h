//
// Created by restarhalf on 2025/5/29.
//

#ifndef IMAGE_H
#define IMAGE_H
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <stdexcept>
#include "Renderer.h"
#include "ResourceLoader.h"

namespace lyt
{
    /**
     * @brief 图像类，负责处理图片资源的加载、显示和管理
     */
    class Image
    {
    private:
        SDL_Texture*  texture = nullptr;  ///< 图像纹理指针
        SDL_Surface*  surface = nullptr;  ///< 图像表面指针
        SDL_Rect      rect;  ///< 图像矩形区域
        SDL_Color     color;  ///< 图像颜色
        std::string   filePath;  ///< 图像文件路径
        Renderer*     renderer;  ///< 渲染器指针
        SDL_BlendMode blendMode = SDL_BLENDMODE_BLEND;  ///< 混合模式
        Uint8         alpha     = 255;  ///< 透明度

    public:
        /**
         * @brief 默认构造函数
         */
        Image();

        /**
         * @brief 析构函数，负责清理图像资源
         */
        ~Image();

        /**
         * @brief 绘制图像
         */
        void draw();

        /**
         * @brief 设置图像属性
         * @param filePath 图像文件路径
         * @param renderer 渲染器指针
         * @param rect 图像矩形区域
         * @param blendMode 混合模式
         * @param alpha 透明度
         */
        void setImage(const std::string& filePath, Renderer* renderer, SDL_Rect rect, SDL_BlendMode blendMode,
                      Uint8 alpha);

        /**
         * @brief 从资源加载图片
         * @param resourceName 资源名称
         * @param renderer 渲染器指针
         * @param rect 图像矩形区域
         * @param blendMode 混合模式
         * @param alpha 透明度
         */
        void setImageFromResource(const char* resourceName, Renderer* renderer, SDL_Rect rect,
                                  SDL_BlendMode blendMode = SDL_BLENDMODE_BLEND, Uint8 alpha = 255);

        // Getters and setters
        [[nodiscard]] SDL_Rect      getRect() const;
        void                        setRect(const SDL_Rect& rect);
        [[nodiscard]] SDL_Color     getColor() const;
        void                        setColor(const SDL_Color& color);
        [[nodiscard]] std::string   getFilepath() const;
        void                        setFilepath(const std::string& file_path);
        [[nodiscard]] Renderer*     getRenderer() const;
        void                        setRenderer(Renderer* renderer);
        [[nodiscard]] SDL_BlendMode getBlendmode() const;
        void                        setBlendmode(SDL_BlendMode blend_mode);
        [[nodiscard]] Uint8         getAlpha() const;
        void                        setAlpha(Uint8 alpha);
    };
}  // namespace lyt
#endif  // IMAGE_H
