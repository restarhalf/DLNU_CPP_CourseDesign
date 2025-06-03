#include "PlayerFish.h"

namespace lx 
{

    PlayerFish::PlayerFish(float x, float y)
        : Fish(x, y, 20.0f) 
	{
        float baseSpeed = 3.0f / (size * 0.3f);    // 计算速度分量
        velocity.x =baseSpeed;
        velocity.y =baseSpeed;

    } // 默认大小,请ui和算法根据实际需求调整

    void PlayerFish::move() 
    {
        position.x += velocity.x;
        position.y += velocity.y;//位置更新
        position.x = std::max(0.0f, std::min(position.x, screenWidth - size));//边界处理
        position.y = std::max(0.0f, std::min(position.y, screenHeight - size));
    }

    void PlayerFish::handleInput(char key) 
    {
        switch (key) 
        {
        case 'w': velocity.y = -2; break; // 上
        case 's': velocity.y = 2; break; // 下
        case 'a': velocity.x = -2; break; // 左
        case 'd': velocity.x = 2; break; // 右
        }
    }

    void PlayerFish::stop() 
    {
        velocity = { 0, 0 };
    }

}

#include "PlayerFish.h"

namespace lx {

    // PlayerFish 类的构造函数
    // 初始化列表调用基类 Fish 的构造函数进行基本初始化
    // 并初始化 PlayerFish 类自身的成员变量
    PlayerFish::PlayerFish(SDL_Renderer* renderer, int x, int y, int width, int height)
        : Fish(renderer, x, y, width, height),
        movingUp(false), movingDown(false),
        movingLeft(false), movingRight(false),
        speed(5), dead(false)
    {
        // 构造函数体为空，因为初始化工作已在初始化列表完成
    }

    // 更新 PlayerFish 的状态（位置等）
    // 参数：
    // windowW - 窗口宽度
    // windowH - 窗口高度
    void PlayerFish::update(int windowW, int windowH)
    {
        if (dead) return;  // 如果鱼已死亡，直接返回，不进行后续更新

        // 根据移动方向标记更新鱼的坐标
        if (movingUp) y -= speed;
        if (movingDown) y += speed;
        if (movingLeft) x -= speed;
        if (movingRight) x += speed;

        // 检查并修正鱼的坐标，使其不超出窗口边界
        if (x < 0) x = 0;
        if (x + width > windowW) x = windowW - width;
        if (y < 0) y = 0;
        if (y + height > windowH) y = windowH - height;

        // 更新 SDL 矩形（用于渲染等）的属性（坐标、宽度、高度）
        rect.x = x;
        rect.y = y;
        rect.w = width;
        rect.h = height;
    }

    // 尝试让 PlayerFish 吃鱼（处理吃鱼逻辑及判断自身是否死亡）
    // 参数：
    // other - 另一条 Fish 对象的引用
    bool PlayerFish::tryEat(Fish& other)
    {
        if (dead) return false;  // 如果自身已死亡，直接返回 false

        if (this!= &other && isCollide(other))  // 不是同一条鱼且发生碰撞
        {
            if (size > other.getSize())  // 如果自身尺寸大于目标鱼尺寸
            {
                size += other.getSize() / 3;  // 增加自身尺寸
                width = height = size;  // 更新宽度和高度（假设鱼是方形）
                rect.w = width;
                rect.h = height;
                return true;  // 返回 true 表示成功吃鱼
            }
            else if (size < other.getSize())  // 如果自身尺寸小于目标鱼尺寸
            {
                dead = true;  // 设置自身为死亡状态
                return false;  // 返回 false 表示被吃（自身死亡）
            }
        }
        return false;  // 其他情况（如未碰撞等）返回 false
    }

    // 设置向上移动标记的方法
    // 参数：
    // pressed - 布尔值，表示是否按下向上移动键
    void PlayerFish::moveUp(bool pressed) { movingUp = pressed; }

    // 设置向下移动标记的方法
    // 参数：
    // pressed - 布尔值，表示是否按下向下移动键
    void PlayerFish::moveDown(bool pressed) { movingDown = pressed; }

    // 设置向左移动标记的方法
    // 参数：
    // pressed - 布尔值，表示是否按下向左移动键
    void PlayerFish::moveLeft(bool pressed) { movingLeft = pressed; }

    // 设置向右移动标记的方法
    // 参数：
    // pressed - 布尔值，表示是否按下向右移动键
    void PlayerFish::moveRight(bool pressed) { movingRight = pressed; }

    // 判断 PlayerFish 是否死亡的常量成员函数
    bool PlayerFish::isDead() const { return dead; }

} // namespace lx
