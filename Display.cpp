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
        this->font = TTF_OpenFont("../assets/MotionPicture.ttf", 100);
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
    std::string directory = "../assets/bg.png";
    SDL_RenderClear(renderer);
    SDL_Texture* texture = IMG_LoadTexture(this->renderer,directory.c_str());
    if(texture != NULL) {
        SDL_RenderCopy(this->renderer, texture, NULL, NULL);
    }
}

//under fixing, current state is too spagetti
void Display::drawMenu(Vector2D Mouse){
    drawBG();
    std::vector<std::string> menu = {"Let's Play","Scoreboard","Quit        "};
    Vector2D OFFSET(20,20),buttonDimensions(160,50);
    int gap = 55;
    SDL_Color normalColor = {.r = 21, .g = 61, .b = 179, .a = 255};
    SDL_Color hoverColor = {.r = 255, .g = 61, .b = 179, .a = 255};

    for (size_t i = 0;i<menu.size();i++) {

        SDL_Rect destRect = {
                .x = (int)OFFSET.x,
                .y = (int)OFFSET.y + (int)i * gap,
                .w = (int)buttonDimensions.x,
                .h = (int)buttonDimensions.y
        };
        ;
        if(Playground::CollisionCheck(Vector2D(destRect.x,destRect.y),Vector2D(destRect.w,destRect.h),Mouse,Vector2D(1.0,1.0))) {
            MenuItem item(menu[i].c_str(), hoverColor, destRect);
            item.Draw(renderer,font);
        }
        else {
            MenuItem item(menu[i].c_str(), normalColor, destRect);
            item.Draw(renderer,font);
        }
    }
}
int Display::getScreenHeight() const {
    return screenHeight;
}

int Display::getScreenWidth() const {
    return screenWidth;
}

Display::~Display() {
    TTF_CloseFont(this->font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}
void Display::drawScoreBoard(SDL_Renderer *renderer) {

}
