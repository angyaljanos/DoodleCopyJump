//
// Created by jani on 2020. 04. 24..
//
#include <string>
#include "SDL.h"
#include "SDL2_gfxPrimitives.h"
#include "SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "Display.h"




void Display::setup(const int w,const int h) {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        SDL_Log("Nem indithato az SDL: %s", SDL_GetError());
        exit(1);
    }
    this->window = SDL_CreateWindow("DoodleJömp", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, 0);
    if (window == NULL) {
        SDL_Log("Nem hozhato letre az ablak: %s", SDL_GetError());
        exit(2);
    }
    this->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (renderer == NULL) {
        SDL_Log("Nem hozhato letre a megjelenito: %s", SDL_GetError());
        exit(3);
    }
    TTF_Init();
    this->font = TTF_OpenFont("assets/MotionPicture",30);
    if(font == NULL){
        SDL_Log("Nem hozhato letre a Betutipus");
        exit(3);
    }
    if(IMG_Init(IMG_INIT_JPG |IMG_INIT_PNG) == 0)
    {
        SDL_Log("Kepmegjelenitesi hiba");
        exit(4);
    }
    SDL_RenderClear(renderer);
}
//under fixing, current state is too spagetti
void Display::drawMenu(Vector2D mousePos){
    std::string menu[] = {"Play","ScoreBoard","Quit"};
    Vector2D OFFSET(100,100),buttonProperties(160,50);
    int gap = 25;
    SDL_Rect drawingRect = {.x = 0, .y = 0,.w = this->screenWidth,.h = this->screenHeight};
    SDL_Texture* texture = IMG_LoadTexture(this->renderer,"assets/bg.png");
    SDL_RenderCopy(this->renderer,texture,NULL, NULL);
    SDL_Color color = {.r = 21, .g = 61, .b = 179, .a = 255};
    for (int i = 0; i < menu->size(); ++i) {
        drawingRect = {.x = (int)OFFSET.x, .y = (int)OFFSET.y + i * gap, .w = (int)buttonProperties.x, .h = (int)buttonProperties.y};
        SDL_Surface* surface = TTF_RenderUTF8_Blended(font, menu[i].c_str(), color);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

        //SDL_RenderCopy(this->renderer,texture,)
    }
}
int Display::getScreenHeight() const {
    return screenHeight;
}

Display::~Display() {
    TTF_CloseFont(this->font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

}
