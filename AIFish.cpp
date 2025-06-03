#include "AIFish.h"
#include <cstdlib>
#include<ctime>
#include<algorithm>
namespace lx 
{

    AIFish::AIFish(float x, float y)
        : Fish(x, y, 0) 
    {
        std::srand(static_cast<unsigned>(std::time(nullptr)));
        // 初始速度（方向随机，速度与大小成反比）
        //此处请算法自行修改！！！！！！！！！！！！！！！！！！，知道了知道了在改了
        size = 10.0f + static_cast<float>(rand() % 91); // 10-100随机大小
        updateVelocity();//随机速度跟方向
    }
    
    void AIFish::move() 
    {
        //边界检测
        //到边界随机更新方向

        if (checkBounds()) {
            updataVelocity();
        }

        //更新位置
        position.x += velocity.x;
        position.y += velocity.y;
        //保证不出边界
        position.x = std::max(0.0f, std::min(position.x, screenWidth - size));
        position.y = std::max(0.0f, std::min(position.y, screenHeight - size));

    }
  
    void AIFish::updataVelocity()const
    {
        // 随机改变方向且速度与大小成反比
        float baseSpeed = 3.0f / (size * 0.3f);
        // 随机方向（角度，0-2π）
        float angle = (rand() % 360) * 3.1415926f / 180.0f;

        // 计算速度分量
        velocity.x = std::cos(angle) * baseSpeed;
        velocity.y = std::sin(angle) * baseSpeed;

        // 限制最小速度（避免大鱼完全静止...）
        float minSpeed = 0.3f;
        float currentSpeed = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
        if (currentSpeed < minSpeed) {
            velocity.x = (velocity.x / currentSpeed) * minSpeed;
            velocity.y = (velocity.y / currentSpeed) * minSpeed;
        }
    }
}


#include "AIFish.h"
#include <cstdlib>

namespace lx {

    // AIFish 类的构造函数
    // 参数：
    // renderer - SDL 渲染器指针
    // x - 鱼的 x 坐标
    // y - 鱼的 y 坐标
    // width - 鱼的宽度
    // height - 鱼的高度
    AIFish::AIFish(SDL_Renderer* renderer, int x, int y, int width, int height)
        : Fish(renderer, x, y, width, height)  // 调用基类 Fish 的构造函数进行初始化
    {
        // 随机设置鱼在 x 轴方向的速度（2.0f 或 -2.0f）
        vx = (rand() % 2 == 0)? 2.0f : -2.0f;
    }

    // 更新鱼的状态（位置等）
    // 参数：
    // windowW - 窗口宽度
    // windowH - 窗口高度
    void AIFish::update(int windowW, int windowH)
    {
        // 根据速度 vx 更新鱼的 x 坐标（转换为整数，因为矩形坐标通常是整数）
        x += static_cast<int>(vx);
        // 检查鱼是否超出窗口左右边界
        if (x < 0 || x + width > windowW)
        {
            reverseDirection();  // 反转鱼的运动方向
            x += static_cast<int>(vx);  // 再次根据新的速度更新坐标（因为反转后速度变号，这里调整位置）
        }
        // 更新 SDL 矩形（用于渲染等）的属性（坐标、宽度、高度）
        rect.x = x;
        rect.y = y;
        rect.w = width;
        rect.h = height;
    }

    // 尝试让当前鱼吃另一条鱼（如果满足条件）
    // 参数：
    // other - 另一条 Fish 类对象（引用）
    bool AIFish::tryEat(Fish& other)
    {
        // 检查条件：不是同一条鱼、发生碰撞、当前鱼的尺寸大于另一条鱼的尺寸
        if (this!= &other && isCollide(other) && size > other.getSize())
        {
            // 增加当前鱼的尺寸（增加量为另一条鱼尺寸的三分之一）
            size += other.getSize() / 3;
            // 根据新尺寸更新鱼的宽度和高度（假设鱼是方形的，宽度和高度相同）
            width = height = size;
            // 更新 SDL 矩形的宽度和高度属性
            rect.w = width;
            rect.h = height;
            return true;  // 表示成功吃到鱼
        }
        return false;  // 表示未吃到鱼
    }

    // 反转鱼在 x 轴方向的运动速度
    void AIFish::reverseDirection()
    {
        vx = -vx;  // 速度取反
    }

} // namespace lx
