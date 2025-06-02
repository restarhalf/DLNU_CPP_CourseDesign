//
// Created by restarhalf on 25-6-1.
//

#include "Music.h"

/**
 * @brief 默认构造函数，初始化音乐指针和状态
 */
Music::Music() : music(nullptr), isPlaying(false) {}

/**
 * @brief 析构函数，释放音乐资源
 */
Music::~Music()
{
    if (music)
    {
        Mix_FreeMusic(music);
        music = nullptr;
    }
}

/**
 * @brief 播放音乐文件
 * @param filePath 音乐文件路径
 */
void Music::playMusic(const std::string& filePath)
{
    // 如果已经有音乐在播放，先停止它
    if (isPlaying)
    {
        stopMusic();
    }

    // 加载新的音乐文件
    music = Mix_LoadMUS(filePath.c_str());
    if (!music)
    {
        SDL_Log("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
        return;
    }

    // 开始播放音乐，设置为循环播放(-1)
    if (Mix_PlayMusic(music, -1) < 0)
    {
        SDL_Log("Failed to play music! SDL_mixer Error: %s\n", Mix_GetError());
        return;
    }

    this->filePath = filePath;
    isPlaying = true;
}

/**
 * @brief 停止当前正在播放的音乐
 */
void Music::stopMusic()
{
    if (music && isPlaying)
    {
        Mix_HaltMusic();
        Mix_FreeMusic(music);
        music = nullptr;
        isPlaying = false;
    }
}