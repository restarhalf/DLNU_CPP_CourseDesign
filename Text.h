//
// Created by restarhalf on 2025/5/29.
//

#ifndef TEXT_H
#define TEXT_H
#include <SDL_egl.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include "Renderer.h"


class Text{
private:
    //字体
     SDL_Texture *texture;

public:
    //构造函数和析构函数
    Text();
    ~Text();


    //绘制文字
    Renderer *drawText(Renderer *render, TTF_Font *font, const std::string &text, SDL_Rect rect,
                       SDL_Color color);

};



#endif //TEXT_H
