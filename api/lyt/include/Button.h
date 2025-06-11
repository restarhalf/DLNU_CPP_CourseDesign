/**
 * @file Button.h
 * @brief 按钮类头文件，负责处理交互式按钮的显示和事件响应
 * @author restarhalf
 * @date 2025/5/30
 */

#ifndef BUTTON_H
#define BUTTON_H
#include "Image.h"
#include "Renderer.h"
#include <SDL.h>
#include "Text.h"
#include <string>
#include <cmath>

namespace lyt
{
    /**
     * @brief 按钮类，负责处理交互式按钮的显示和事件响应
     *
     * 提供两种按钮样式：
     * 1. 纯色按钮：使用SDL绘制的带圆角的纯色矩形按钮，可以添加文字
     * 2. 图片按钮：使用图片作为按钮背景，支持悬停和点击效果
     */
    class Button
    {
    private:
        SDL_Rect      rect{};             ///< 按钮区域（位置和尺寸）
        SDL_Color     buttonColor{};      ///< 按钮颜色（用于纯色按钮）
        TTF_Font     *font{};             ///< 按钮文字字体
        SDL_Color     textColor{};        ///< 文字颜色
        Text          text;               ///< 按钮文字对象
        Image         image;              ///< 按钮图片对象
        std::string   filePath;           ///< 图片文件路径
        Renderer     *renderer{};         ///< 渲染器指针
        SDL_Texture  *texture{};          ///< 按钮纹理
        SDL_Surface  *surface{};          ///< 按钮表面
        bool          isClicked{false};   ///< 按钮是否被点击（鼠标按下且在按钮区域内）
        bool          isPressed{false};    ///< 按钮是否被按下（鼠标在按钮区域内按下）
        bool          isReleased{true};  ///< 按钮是否被释放（鼠标在按钮区域内释放）
        bool          isInside{false};    ///< 鼠标是否在按钮区域内
        SDL_BlendMode blendMode;          ///< 混合模式（用于透明度和颜色混合）
        Uint8         alpha{255};         ///< 透明度（0-255）

    public:
        /**
         * @brief 默认构造函数，初始化按钮的基本属性
         */
        Button() = default;

        /**
         * @brief 默认析构函数
         */
        ~Button() = default;

        /**
         * @brief 检查按钮是否被点击（鼠标按下）
         * @return true 如果按钮被点击，false 否则
         */
        [[nodiscard]] bool isButtonClicked() const;

        /**
         * @brief 检查按钮是否被释放（鼠标抬起）
         * @return true 如果按钮被释放，false 否则
         * @note 此状态仅在鼠标在按钮区域内释放时为true，且仅持续一帧
         */
        [[nodiscard]] bool isButtonReleased() const;

        /**
         * @brief 检查按钮是否被按住
         * @return true 如果按钮被按住，false 否则
         */
        [[nodiscard]] bool isButtonPressed() const;

        /**
         * @brief 绘制纯色按钮
         * @note 会绘制一个带圆角的纯色矩形，如果设置了文本也会绘制文本
         */
        void draw();

        /**
         * @brief 绘制图片按钮
         * @note 会根据按钮状态（普通、悬停、点击）调整图片的透明度
         */
        void drawwithImage();

        /**
         * @brief 处理按钮事件
         * @param event SDL事件对象，处理鼠标点击、释放和移动事件
         * @note 根据鼠标事件更新按钮状态，并处理悬停效果
         */
        void handleEvent(const SDL_Event &event);

        /**
         * @brief 设置按钮属性（使用独立的坐标和尺寸参数）
         * @param x 按钮左上角的x坐标
         * @param y 按钮左上角的y坐标
         * @param w 按钮宽度
         * @param h 按钮高度
         * @param color 按钮颜色
         */
        void setButton(int x, int y, int w, int h, SDL_Color color);

        /**
         * @brief 设置按钮属性（使用SDL_Rect结构）
         * @param rect 按钮的矩形区域（位置和尺寸）
         * @param color 按钮颜色
         */
        void setButton(SDL_Rect rect, SDL_Color color);

        /**
         * @brief 设置按钮属性（使用image的情况）
         * @param rect 按钮的矩形区域（位置和尺寸）
         */
        void setButtonwithImage(SDL_Rect rect);

        /**
         * @brief 设置按钮文本
         * @param text 文本内容
         * @param font 字体指针（TTF_Font*）
         * @param color 文本颜色
         * @param renderer 渲染器指针
         * @param blendMode 混合模式，默认为SDL_BLENDMODE_BLEND
         * @param alpha 透明度，默认为255（完全不透明）
         * @note 文本会自动缩放以适应按钮大小，并在按钮内居中显示
         */
        void setText(const std::string &text, TTF_Font *font, SDL_Color color, Renderer *renderer,
                     SDL_BlendMode blendMode = SDL_BLENDMODE_BLEND, Uint8 alpha = 255);

        /**
         * @brief 设置图片按钮
         * @param filePath 图片文件路径
         * @param renderer 渲染器指针
         * @param rect 按钮的矩形区域
         * @param blendMode 混合模式，默认为SDL_BLENDMODE_BLEND
         * @param alpha 透明度，默认为255（完全不透明）
         * @throws std::runtime_error 如果图片加载失败
         */
        void setButtonwithImage(const std::string &filePath, Renderer *renderer, SDL_Rect rect,
                               SDL_BlendMode blendMode = SDL_BLENDMODE_BLEND, Uint8 alpha = 255);
    };
}  // namespace lyt

#endif  // BUTTON_H
