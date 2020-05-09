//
// Created by jani on 2020. 04. 24..
//
#include <string>
#include <vector>
//#include "SDL2_gfxPrimitives.h"
//#include "SDL_image.h"
//#include "SDL2/SDL_ttf.h"
#include "Display.h"
#include "SDL_Fake.h"
#include "MenuItem.hpp"
#include "Playground.h"

#include "memtrace.h"
void Display::setup(const int w,const int h) {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        SDL_Log("Nem indithato az SDL: %s", SDL_GetError());
        exit(1);
    }

    this->window = SDL_CreateWindow("DoodleCopyJump", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, 0);
    if (window == NULL) {
        SDL_Log("Nem hozhato letre az ablak: %s", SDL_GetError());
        exit(2);
    }

    this->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (renderer == NULL) {
        SDL_Log("Nem hozhato letre a megjelenito: %s", SDL_GetError());
        exit(3);
    }

    if(TTF_Init() == 0) {
        this->font = TTF_OpenFont("../assets/MotionPicture.ttf", 150);
        if (font == NULL) {
            SDL_Log("Nem hozhato letre betutipus");
            exit(3);
        }
    }
    if(IMG_Init(IMG_INIT_JPG |IMG_INIT_PNG) == 0)
    {
        SDL_Log("Kepmegjelenitesi hiba");
        exit(4);
    }
    SDL_RenderClear(renderer);
}

void Display::drawBG(){
    //SDL_Delay(200);
    SDL_Rect drawingRect = {.x = 0, .y = 0,.w = screenWidth,.h = screenHeight};

    SDL_RenderClear(renderer);

    if( background != NULL) {
        SDL_RenderCopy(this->renderer, background, NULL, NULL);
    }else std::cerr<<"Failed to load background"<<std::endl;
}



int Display::getScreenHeight() const {
    return screenHeight;
}

int Display::getScreenWidth() const {
    return screenWidth;
}

Display::~Display() {
    SDL_DestroyTexture(background);
    TTF_CloseFont(this->font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}
void Display::drawScoreBoard(SDL_Renderer *renderer) {

}

Display::Display(const int w ,const int h ):
        screenWidth(w), screenHeight(h){
    setup( w, h);
    std::string directory = "../assets/bg.png";
    background = IMG_LoadTexture(this->renderer,directory.c_str());
}

TTF_Font *Display::getFont() const {
    return font;
}
