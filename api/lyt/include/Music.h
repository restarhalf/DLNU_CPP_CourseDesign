//
// Created by restarhalf on 25-6-1.
//

#ifndef MUSIC_H
#define MUSIC_H
#include <SDL.h>
#include <SDL_mixer.h>
#include <string>
class Music
{
private:
    Mix_Music*  music;
    std::string filePath;
    bool        isPlaying;
public:
    Music();
    ~Music();
    void playMusic(const std::string& filePath);
    void stopMusic();

};


#endif  // MUSIC_H
