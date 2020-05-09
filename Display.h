//
// Created by jani on 2020. 04. 24..
//

#ifndef NAGYHAZI_DISPLAY_H
#define NAGYHAZI_DISPLAY_H

//#include "SDL2_gfxPrimitives.h"
//#include "SDL_image.h"
//#include "SDL_ttf.h"
#include "Vector2D.h"
#include "SDL_Fake.h"
#include <vector>
#include "memtrace.h"
class Display{
private:
    int screenWidth,screenHeight;
    SDL_Window* window;
    TTF_Font* font;
    SDL_Texture* background;
    Display& operator=(const Display&){ return *this;}
    Display(const Display& d){}

public:
    SDL_Renderer* renderer;

    Display(const int w = 360,const int h = 570);

    void setup(const int w,const int h);

    void drawScoreBoard(SDL_Renderer* renderer);

    int getScreenHeight() const;

    int getScreenWidth() const;

    TTF_Font *getFont() const;

    void drawBG();

    ~Display();
};
#endif //NAGYHAZI_DISPLAY_H
