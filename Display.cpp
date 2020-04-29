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
    std::string directory = "../assets/bg.png";
    SDL_RenderClear(renderer);
    SDL_Texture* texture = IMG_LoadTexture(this->renderer,directory.c_str());
    if(texture != NULL) {
        SDL_RenderCopy(this->renderer, texture, NULL, NULL);
    }
}

void Display::drawMenu(Vector2D Mouse){
    drawBG();
    SDL_Color hoverColor = {.r =0 ,.g = 115, .b = 8,.a = 200};
    SDL_Color normalColor = {.r =255 ,.g = 0, .b = 0,.a = 200};
    for(size_t i = 0; i < items.size(); ++i) {
        items[i]->Draw(renderer,this->font);
        if(Playground::CollisionCheck(Vector2D(items[i]->getPos().x,items[i]->getPos().y),
                Vector2D(items[i]->getPos().w,items[i]->getPos().y),Mouse,Vector2D(5,5)))
        {
            items[i]->setCol(hoverColor);
        }
        else items[i]->setCol(normalColor);
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

int Display::chooseMenu(Vector2D MousePosition) {
    int choosen = -1;
    SDL_Event event;
    SDL_WaitEvent(&event);
    if(event.type == SDL_MOUSEBUTTONDOWN)
        for (size_t i = 0; i < items.size(); i++) {
            {
                if(Playground::CollisionCheck(Vector2D(items[i]->getPos().x,items[i]->getPos().y),
                                              Vector2D(items[i]->getPos().w,items[i]->getPos().y),
                                              MousePosition,
                                              Vector2D(5,5)))
                {
                    choosen = i;
                }
            }
    }
    return choosen;
}

Display::Display(const int w ,const int h ,const std::vector<std::string>& subtitle):
        screenWidth(w), screenHeight(h){
    setup( w, h);
    items.resize(subtitle.size());
    Vector2D OFFSET(20,20),buttonDimensions(160,50);
    int gap = 55;
    for (int i = 0; i < subtitle.size(); ++i) {
        SDL_Rect destRect = {
                .x = (int)OFFSET.x,
                .y = (int)OFFSET.y + (int)i * gap,
                .w = (int)buttonDimensions.x,
                .h = (int)buttonDimensions.y
        };
        items[i] = new MenuItem(subtitle[i].c_str(), destRect);
    }
    //std::cout<<subtitle.size()<<std::endl;
}