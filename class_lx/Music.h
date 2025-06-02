#pragma once

#ifndef MUSIC_H
#define MUSIC_H
#include <SDL.h>
#include <SDL_mixer.h>
#include <string>

/**
 * @brief 音乐类，负责处理背景音乐的播放和控制
 */
class Music
{
private:
    Mix_Music* music;  ///< SDL_mixer音乐对象指针
    std::string filePath;  ///< 音乐文件路径
    bool        isPlaying;  ///< 音乐播放状态标志

public:
    /**
     * @brief 默认构造函数
     */
    Music();

    /**
     * @brief 析构函数，负责清理音乐资源
     */
    ~Music();

    /**
     * @brief 播放音乐文件
     * @param filePath 音乐文件路径
     */
    void playMusic(const std::string& filePath);

    /**
     * @brief 停止当前正在播放的音乐
     */
    void stopMusic();
};

#endif  // MUSIC_H