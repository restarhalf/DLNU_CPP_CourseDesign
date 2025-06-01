//
// Created by restarhalf on 25-6-1.
//

#ifndef MIXER_H
#define MIXER_H
#include<SDL_mixer.h>
namespace lyt
{

    class Mixer
    {
    private:
        // 音乐
        Mix_Music *music;
        // 音效
        Mix_Chunk *chunk;
        // 音量
        int volume;
        // 声道
        int channel;
        // 混音器
        Mixer *mixer;
        // 循环次数
        int loops;
    public:
        Mixer() = default;
        ~Mixer() = default;
        void mix();
    };

}  // namespace lyt

#endif  // MIXER_H
