/**
 * @file ScoreManager.cpp
 * @brief 分数管理器实现，负责管理当前分数和最高分
 */

#include "ScoreManager.h"

#include <algorithm>
#include <fstream>

namespace lx
{

    /**
     * @brief 构造函数，初始化分数并从文件读取最高分
     */
    ScoreManager::ScoreManager() : score(0), highScore(0)
    {
        std::ifstream file(filename);
        if (file.is_open()) file >> highScore;
    }

    /**
     * @brief 增加分数，并更新最高分
     * @param value 要增加的分数值
     */
    void ScoreManager::add(int value)
    {
        score += value;
        highScore = std::max(score, highScore);
    }

    /**
     * @brief 获取当前分数
     * @return 当前分数
     */
    int ScoreManager::getScore() const { return score; }

    /**
     * @brief 获取最高分
     * @return 历史最高分
     */
    int ScoreManager::getHighScore() const { return highScore; }

    /**
     * @brief 保存最高分到文件
     */
    void ScoreManager::saveHighScore()
    {
        std::ofstream file(filename);
        if (file.is_open()) file << highScore;
    }

    /**
     * @brief 重置当前分数为0
     */
    void ScoreManager::reset()
    {
        score = 0;
    }

}  // namespace lx
