//
// Created by jani on 2020. 04. 24..
//

#ifndef NAGYHAZI_DISPLAY_H
#define NAGYHAZI_DISPLAY_H

#include "SDL.h"
#include "SDL2_gfxPrimitives.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "Vector2D.h"

class Display{
private:
    int screenWidth,screenHeight;
    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* font;


    Display& operator=(const Display&){ return *this;}
    Display(const Display& d){}
public:
    Display(const int w = 360,const int h = 570): screenWidth(w), screenHeight(h){
        setup( w, h);
    }


    void setup(const int w,const int h);

    void drawMenu(Vector2D OFFSET);

    void showMenu(Vector2D mousePos);

    int getScreenHeight() const;

    int getScreenWidth() const;

    ~Display();
};
#endif //NAGYHAZI_DISPLAY_H
