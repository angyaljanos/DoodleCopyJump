//
// Created by jani on 2020. 04. 26..
//
#include "Platform.h"
#include "SDL_Fake.h"

#include "memtrace.h"
int Platform::gap = 30;
int Platform::maxGap = 120;
double Platform::platHeight = 15;
double Platform::platWidth = 58;

void Platform::Draw(SDL_Renderer *renderer) const {
    SDL_Rect rect = {.x = (int)pos.x, .y = (int)pos.y,
                     .w = (int)dims.x,.h = (int)dims.y};
    SDL_RenderCopy(renderer,texture,NULL,&rect);
}
void Platform::Update(Character& c,Display& d) {}