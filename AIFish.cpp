#include "AIFish.h"

namespace lx {

    // 构造函数，初始化AI鱼的速度、方向和分数值
    AIFish::AIFish(lyt::Renderer* renderer, const std::string& imagePath, int x, int y, int w, int h)
        : Fish(renderer, imagePath, x, y, w, h) {
        speed = 1 + rand() % 3; // 随机速度1~3
        direction = rand() % 2 == 0 ? -1 : 1; // 随机初始方向
		scoreValue = std::max(1, w / 5); // 分数值初始为宽度的1/5，至少为1
    }
	//这个分数的比例好像过大，需要调整
    // 更新AI鱼的位置，并在碰到窗口边界时反向
    void AIFish::update(int windowW, int windowH) {
        rect.x += direction * speed;
        if (rect.x <= 0 || rect.x + rect.w >= windowW) {
			direction *= -1; // 碰到边界时反向，用于测试，建议让鱼直接消失，头文件有个kill可以用
			// rect.x = std::max(0, std::min(rect.x, windowW - rect.w)); // 保持在窗口内
        }
    }

    // 让AI鱼变大，并重新计算分数值
    void AIFish::grow(float scale) {
        Fish::grow(scale);
        scoreValue = (rect.w * rect.h) / 10;
    }
    int AIFish::getScoreValue() const {
        return scoreValue;
    }


} // namespace lx
