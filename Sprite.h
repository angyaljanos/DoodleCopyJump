//
// Created by jani on 2020. 04. 25..
//

#ifndef NAGYHAZI_SPRITE_H
#define NAGYHAZI_SPRITE_H

#include "Vector2D.h"
#include "SDL_Fake.h"
//#include "SDL2_gfxPrimitives.h"
//#include "SDL_image.h"
//#include "SDL2/SDL_ttf.h"
#include "Display.h"


struct Sprite{
    Vector2D pos,dims;
    SDL_Texture* texture;

    Sprite(){}
    Sprite(Vector2D pos,Vector2D dims, const char* PATH, SDL_Renderer* renderer):pos(pos),dims(dims){
        texture = IMG_LoadTexture(renderer,PATH);
    }

    Sprite(double x ,double y,double w, double h, const char* PATH, SDL_Renderer* renderer):pos(x,y),dims(w,h){
        texture = IMG_LoadTexture(renderer,PATH);
    }

    //virtual void Update(Display& display) = 0;
    virtual void Draw(SDL_Renderer* renderer) const = 0;

    virtual ~Sprite(){
        SDL_DestroyTexture(texture);
    }
};
#endif //NAGYHAZI_SPRITE_H
