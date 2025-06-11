#pragma once
#include <string>

namespace lx
{

    /**
     * @brief 分数管理器类，负责当前分数和最高分的管理与持久化
     */
    class ScoreManager
    {
    public:
        /**
         * @brief 构造函数，初始化分数和读取最高分
         */
        ScoreManager();

        /**
         * @brief 增加分数
         * @param value 要增加的分数值
         */
        void add(int value);

        /**
         * @brief 获取当前分数
         * @return 当前分数
         */
        int getScore() const;

        /**
         * @brief 获取最高分
         * @return 历史最高分
         */
        int getHighScore() const;

        /**
         * @brief 保存最高分到文件
         */
        void saveHighScore();

        /**
         * @brief 重置当前分数为0
         */
        void reset();

    private:
        int score;      ///< 当前分数
        int highScore;  ///< 最高分
        const std::string filename = "highscore.txt";  ///< 最高分保存文件名
    };

}  // namespace lx
