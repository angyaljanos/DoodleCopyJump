//
// Created by jani on 2020. 04. 25..
//

#ifndef NAGYHAZI_PLATFORM_H
#define NAGYHAZI_PLATFORM_H
#include "SDL.h"
#include "SDL2_gfxPrimitives.h"
#include "SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "Sprite.h"
#include "Character.h"
class Platform:public Sprite{
public:
    static double platHeight;
    static int gap;
    static int maxGap;

    Platform(Vector2D pos, SDL_Renderer* renderer, const char* PATH = "assets/greenF.png",Vector2D dims = Vector2D(58,15)):Sprite(pos,dims,PATH,renderer){

    }

    static void incraseGap(){
        if(Platform::gap < Platform::maxGap)
            gap+=15;
    }
    virtual void Draw(SDL_Renderer* renderer) const;
    virtual void Update(Character& c);
};
#endif //NAGYHAZI_PLATFORM_H
