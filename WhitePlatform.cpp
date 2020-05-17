//
// Created by jani on 2020. 04. 26..
//

#include "WhitePlatform.h"
#include "Playground.h"
#include "SDL_Fake.h"

#include "memtrace.h"

void WhitePlatform::Draw(SDL_Renderer* renderer) const {
    if(!used){
        SDL_Rect rect = {.x = (int)pos.x, .y = (int)pos.y,
                .w = (int)dims.x,.h = (int)dims.y};
        SDL_RenderCopy(renderer,texture,NULL,&rect);
    }
}
void WhitePlatform::Update(Character& c, Display& d){

}
void WhitePlatform::setAsUsed() {
    used = true;
}
