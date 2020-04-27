//
// Created by jani on 2020. 04. 26..
//
#include "Platform.h"
int Platform::gap = 50;
int Platform::maxGap = 150;
double Platform::platHeight = 15;

void Platform::Draw(SDL_Renderer *renderer) const {
    SDL_Rect rect = {.x = (int)pos.x, .y = (int)pos.y,
                     .w = (int)dims.x,.h = (int)dims.y};
    SDL_RenderCopy(renderer,texture,NULL,&rect);
}
void Platform::Update(Character &c) {}