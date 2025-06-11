/**
 * @file Button.cpp
 * @brief 按钮类实现，负责处理交互式按钮的显示和事件响应
 */

#include "Button.h"
namespace lyt
{
    /**
     * @brief 检查按钮是否被点击
     * @return 如果按钮被点击则返回true
     */
    bool Button::isButtonClicked() const { return isClicked; }

    /**
     * @brief 检查按钮是否被释放
     * @return 如果按钮被释放则返回true
     */
    bool Button::isButtonReleased() const { return isReleased; }

    /**
     * @brief 检查按钮是否被按下
     * @return 如果按钮被按下则返回true
     */
    bool Button::isButtonPressed() const { return isPressed; }

    /**
     * @brief 绘制纯色按钮
     */
    void Button::draw()
    {
        // 保存当前渲染器状态
        Uint8 r, g, b, a;
        SDL_GetRenderDrawColor(renderer->get(), &r, &g, &b, &a);
        SDL_BlendMode currentBlendMode;
        SDL_GetRenderDrawBlendMode(renderer->get(), &currentBlendMode);

        // 设置按钮颜色
        SDL_SetRenderDrawColor(renderer->get(), buttonColor.r, buttonColor.g, buttonColor.b, buttonColor.a);
        SDL_SetRenderDrawBlendMode(renderer->get(), blendMode);

        // 圆角半径
        int radius = 15;

        // 绘制中间矩形
        SDL_Rect centerRect = {rect.x + radius, rect.y, rect.w - 2 * radius, rect.h};
        SDL_RenderFillRect(renderer->get(), &centerRect);

        // 绘制左右两侧矩形
        SDL_Rect leftRect  = {rect.x, rect.y + radius, radius, rect.h - 2 * radius};
        SDL_Rect rightRect = {rect.x + rect.w - radius, rect.y + radius, radius, rect.h - 2 * radius};
        SDL_RenderFillRect(renderer->get(), &leftRect);
        SDL_RenderFillRect(renderer->get(), &rightRect);

        // 绘制四个圆角
        for (int w = 0; w < radius; w++)
        {
            for (int h = 0; h < radius; h++)
            {
                const float pk = sqrt(static_cast<float>((radius - w) * (radius - w) + (radius - h) * (radius - h)));
                if (pk <= static_cast<float>(radius))
                {
                    // 左上角
                    SDL_RenderDrawPoint(renderer->get(), rect.x + w, rect.y + h);
                    // 右上角
                    SDL_RenderDrawPoint(renderer->get(), rect.x + rect.w - w - 1, rect.y + h);
                    // 左下角
                    SDL_RenderDrawPoint(renderer->get(), rect.x + w, rect.y + rect.h - h - 1);
                    // 右下角
                    SDL_RenderDrawPoint(renderer->get(), rect.x + rect.w - w - 1, rect.y + rect.h - h - 1);
                }
            }
        }

        // 绘制文本
        SDL_SetTextureAlphaMod(texture, alpha);
        renderer->copy(texture, nullptr, &rect);
        text.draw();

        // 还原渲染器状态
        SDL_SetRenderDrawColor(renderer->get(), r, g, b, a);
        SDL_SetRenderDrawBlendMode(renderer->get(), currentBlendMode);
    }

    /**
     * @brief 绘制带图片的按钮
     */
    void Button::drawwithImage()
    {
        if (isClicked || isPressed)
        {
            // 按下时降低图片的透明度来实现变暗效果
            image.setAlpha(static_cast<Uint8>(alpha * 0.6));
        }
        else if (isInside)
        {
            // 鼠标悬停时降低图片的透明度
            image.setAlpha(static_cast<Uint8>(alpha * 0.8));
        }
        else
        {
            // 未按下时使用正常透明度
            image.setAlpha(alpha);
        }
        image.draw();
    }

    /**
     * @brief 处理按钮事件
     * @param event SDL事件对象
     */
    void Button::handleEvent(const SDL_Event &event)
    {
        int  mouseX, mouseY;

        // 重置released状态（应该只持续一帧）
        isReleased = false;

        switch (event.type)
        {
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    // 检查鼠标是否在按钮区域内
                    mouseX   = event.button.x;
                    mouseY   = event.button.y;
                    isInside = (mouseX >= rect.x && mouseX <= rect.x + rect.w && mouseY >= rect.y &&
                                mouseY <= rect.y + rect.h);
                    if (isInside)
                    {
                        isClicked = true;
                        isPressed = true;
                    }
                }
                break;

            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    // 检查鼠标是否在按钮区域内释放
                    mouseX   = event.button.x;
                    mouseY   = event.button.y;
                    isInside = (mouseX >= rect.x && mouseX <= rect.x + rect.w && mouseY >= rect.y &&
                                mouseY <= rect.y + rect.h);

                    if (isInside && isPressed)
                    {
                        isReleased = true;
                    }
                    isClicked = false;
                    isPressed = false;
                }
                break;
            case SDL_MOUSEMOTION:
                mouseX = event.motion.x;
                mouseY = event.motion.y;
                isInside = (mouseX >= rect.x && mouseX <= rect.x + rect.w &&
                             mouseY >= rect.y && mouseY <= rect.y + rect.h);
                break;
            default:
                break;
        }
    }

    /**
     * @brief 设置按钮属性（使用坐标和尺寸）
     * @param x 按钮左上角X坐标
     * @param y 按钮左上角Y坐标
     * @param w 按钮宽度
     * @param h 按钮高度
     * @param color 按钮颜色
     */
    void Button::setButton(int x, int y, int w, int h, SDL_Color color)
    {
        rect.x = x;
        rect.y = y;
        rect.w = w;
        rect.h = h;
        image.setRect(rect);
        buttonColor = color;  // 设置按钮颜色
        isClicked   = false;  // 重置点击状态
    }

    /**
     * @brief 设置按钮属性（使用SDL_Rect）
     * @param rect 按钮的矩形区域
     * @param color 按钮颜色
     */
    void Button::setButton(SDL_Rect rect, SDL_Color color)
    {
        this->rect = rect;
        buttonColor = color;  // 设置按钮颜色
        isClicked   = false;  // 重置点击状态
    }

    /**
     * @brief 设置按钮区域（用于图像按钮）
     * @param rect 按钮的矩形区域
     */
    void Button::setButtonwithImage(SDL_Rect rect)
    {
        this->rect = rect;
        image.setRect(this->rect);
    }

    /**
     * @brief 设置按钮文本
     * @param text 文本内容
     * @param font 字体指针
     * @param color 文本颜色
     * @param renderer 渲染器指针
     * @param blendMode 混合模式，默认为SDL_BLENDMODE_BLEND
     * @param alpha 透明度，默认为255
     */
    void Button::setText(const std::string &text, TTF_Font *font, SDL_Color color, Renderer *renderer,
                         SDL_BlendMode blendMode, Uint8 alpha)
    {
        this->font      = font;
        this->textColor = color;
        this->renderer  = renderer;
        this->blendMode = blendMode;
        this->alpha     = alpha;

        // 获取文本尺寸
        int textWidth, textHeight;
        TTF_SizeText(font, text.c_str(), &textWidth, &textHeight);

        // 计算缩放比例以适应按钮
        double scaleX = rect.w * 0.8 / textWidth;  // 留出20%的边距
        double scaleY = rect.h * 0.7 / textHeight;  // 选择较小的缩放比例以保持宽高比

        // 计算缩放后的文本尺寸
        int scaledWidth  = static_cast<int>(textWidth * scaleX);
        int scaledHeight = static_cast<int>(textHeight * scaleY);

        // 计算居中位置
        SDL_Rect centeredRect = {rect.x + (rect.w - scaledWidth) / 2,  // 水平居中
                                 rect.y + (rect.h - scaledHeight) / 2,  // 垂直居中
                                 scaledWidth, scaledHeight};

        this->text.setAll(renderer, centeredRect, color, font, blendMode, text);
    }

    /**
     * @brief 设置带图片的按钮
     * @param filePath 图片文件路径
     * @param renderer 渲染器指针
     * @param rect 按钮的矩形区域
     * @param blendMode 混合模式，默认为SDL_BLENDMODE_BLEND
     * @param alpha 透明度，默认为255
     */
    void Button::setButtonwithImage(const std::string &filePath, Renderer *renderer, SDL_Rect rect,
                                    SDL_BlendMode blendMode, Uint8 alpha)
    {
        this->rect      = rect;
        this->blendMode = blendMode;
        this->alpha     = alpha;
        this->filePath  = filePath;
        this->renderer  = renderer;
        try
        {
            image.setImage(this->filePath,this-> renderer, this->rect, this->blendMode, this->alpha);
        }
        catch (const std::exception &e)
        {
            SDL_Log("Failed to load image: %s", e.what());
        }
    }
}  // namespace lyt
