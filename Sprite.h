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
#include "memtrace.h"

///@brief Minden grafikával rendelkező objektum ősosztálya
struct Sprite{
    Vector2D pos,dims;
    SDL_Texture* texture;

    Sprite(){}
    Sprite(Vector2D pos,Vector2D dims, const char* PATH, Display& d):pos(pos),dims(dims){
        texture = IMG_LoadTexture(d.renderer,PATH);
        //std::cout<<"Jó lessz az"<<std::endl;
    }

    virtual void Draw(SDL_Renderer* renderer) const = 0;

    virtual ~Sprite(){
        SDL_DestroyTexture(texture);
    }
};
#endif //NAGYHAZI_SPRITE_H
