//
// Created by jani on 2020. 04. 24..
//
#include <string>
#include <vector>
#include <exception>
#include "Display.h"
#include "SDL_Fake.h"
#include "MenuItem.hpp"
#include "Playground.h"

#include "memtrace.h"
///@brief A rendereléshez szükésges SDL inicializálása
void Display::setup(const int w,const int h) {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        throw std::logic_error(SDL_GetError());
    }

    this->window = SDL_CreateWindow("DoodleCopyJump", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, 0);
    if (window == NULL) {
        throw std::logic_error(SDL_GetError());
    }

    this->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (renderer == NULL) {
        throw std::logic_error(SDL_GetError());
    }

    if(TTF_Init() == 0) {
        this->font = TTF_OpenFont("assets/MotionPicture.ttf", 150);
        if (font == NULL) {
            throw std::logic_error(SDL_GetError());
        }
    }
    if(IMG_Init(IMG_INIT_JPG |IMG_INIT_PNG) == 0)
    {
        throw std::logic_error(SDL_GetError());
    }
    SDL_RenderClear(renderer);
}

///@brief Háttér rajzoló függvény
void Display::drawBG(){
    SDL_Rect drawingRect = {.x = 0, .y = 0,.w = screenWidth,.h = screenHeight};

    SDL_RenderClear(renderer);

    if( background != NULL) {
        SDL_RenderCopy(this->renderer, background, NULL, &drawingRect);
    }else std::logic_error("Failed to load background\n");
}


///@brief A képernyő magasságát visszaadó függvény
int Display::getScreenHeight() const {
    return screenHeight;
}
///@brief A képernyő szélességét visszaadó függvény
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

Display::Display(const int w ,const int h ):
        screenWidth(w), screenHeight(h){
    setup( w, h);
    std::string directory = "assets/bg.png";
    background = IMG_LoadTexture(this->renderer,directory.c_str());
}
///@brief Betűkészletet visszaadó függvény
TTF_Font *Display::getFont() const {
    return font;
}
