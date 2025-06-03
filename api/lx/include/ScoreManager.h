#pragma once
#include <string>

namespace lx {

    // 分数管理器类，负责当前分数和最高分的管理与持久化
    class ScoreManager {
    public:
        ScoreManager(); // 构造函数，初始化分数和读取最高分

        void add(int value);        // 增加分数
        int getScore() const;       // 获取当前分数
        int getHighScore() const;   // 获取最高分
        void saveHighScore();       // 保存最高分到文件

    private:
        int score;                  // 当前分数
        int highScore;              // 最高分
        const std::string filename = "highscore.txt"; // 最高分保存文件名
    };

} // namespace lx
