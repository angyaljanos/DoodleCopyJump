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

class Display{
private:
    int screenWidth,screenHeight;
    SDL_Window* window;

    TTF_Font* font;


    Display& operator=(const Display&){ return *this;}
    Display(const Display& d){}
    void drawBG();
public:
    SDL_Renderer* renderer;
    Display(const int w = 360,const int h = 570): screenWidth(w), screenHeight(h){
        setup( w, h);
    }


    void setup(const int w,const int h);

    void drawMenu(Vector2D Mouse);

    void drawScoreBoard(SDL_Renderer* renderer);

    int getScreenHeight() const;

    int getScreenWidth() const;

    ~Display();
};
#endif //NAGYHAZI_DISPLAY_H
