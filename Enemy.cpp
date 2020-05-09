//
// Created by jani on 2020. 04. 25..
//
#include "Enemy.h"

#include "SDL_Fake.h"
//#include "SDL2_gfxPrimitives.h"
//#include "SDL_image.h"
//#include "SDL2/SDL_ttf.h""
#include "SDL_Fake.h"
#include "Character.h"
#include "memtrace.h"
void Enemy::getKilled(bool alive){
    this->dead = alive;
}
void Enemy::Update(double sinking){
    if(!dead){
        pos += sinking;

    }
}
void Enemy::Draw(SDL_Renderer* renderer) const {
    if(!dead){
        SDL_Rect rect ={.x = (int)this->pos.x, .y = (int)this->pos.y,
                        .w = (int)this->dims.x, .h = (int)this->pos.y };
        if(texture != NULL)
            SDL_RenderCopy(renderer,texture, nullptr,&rect);
    }
};

