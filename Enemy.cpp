//
// Created by jani on 2020. 04. 25..
//
#include "Enemy.h"
#include "SDL_Fake.h"

///@brief Az ellenfél kiírását végző függvénys
void Enemy::Draw(SDL_Renderer* renderer) const {
    if(!dead){
        SDL_Rect rect ={.x = (int)this->pos.x, .y = (int)this->pos.y,
                        .w = (int)this->dims.x, .h = (int)this->dims.y };
        if(texture != NULL)
            SDL_RenderCopy(renderer,texture, NULL,&rect);
    }
}
///@brief Az ellenfél "megölését" végző függvény
void Enemy::setToDead() {
    dead = true;
}

