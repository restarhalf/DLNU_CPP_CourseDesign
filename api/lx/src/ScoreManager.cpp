#include "ScoreManager.h"
#include <fstream>
#include <algorithm>

namespace lx {

    // 构造函数，初始化分数并从文件读取最高分
    ScoreManager::ScoreManager() : score(0), highScore(0) {
        std::ifstream file(filename);
        if (file.is_open()) file >> highScore;
    }

    // 增加分数，并更新最高分
    void ScoreManager::add(int value) {
        score += value;
        highScore = std::max(score, highScore);
    }

    // 获取当前分数
    int ScoreManager::getScore() const { return score; }

    // 获取最高分
    int ScoreManager::getHighScore() const { return highScore; }

    // 保存最高分到文件
    void ScoreManager::saveHighScore() {
        std::ofstream file(filename);
        if (file.is_open()) file << highScore;
    }

} // namespace lx
