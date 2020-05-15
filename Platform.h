//
// Created by jani on 2020. 04. 25..
//

#ifndef NAGYHAZI_PLATFORM_H
#define NAGYHAZI_PLATFORM_H
#include "SDL_Fake.h"
//#include "SDL2_gfxPrimitives.h"
//#include "SDL_image.h"
//#include "SDL2/SDL_ttf.h"
#include "Sprite.h"
#include "Character.h"
#include "SDL_Fake.h"
#include "memtrace.h"
class Platform:public Sprite{
public:
    //platform properties - all of them has the same
    static double platHeight;
    static double platWidth;
    static int gap;
    static int maxGap;

    Platform(Vector2D pos, SDL_Renderer* renderer, const char* PATH = "../assets/green.png",Vector2D dims = Vector2D(58,15)):Sprite(pos,dims,PATH,renderer){
        if(texture == NULL)
            throw std::logic_error("Üres textúra @ Platform");
    }

    static void incraseGap(){
        if(Platform::gap < Platform::maxGap)
            gap+=15;
    }
    virtual void Draw(SDL_Renderer* renderer) const;
    virtual void Update(Character& c);
};
#endif //NAGYHAZI_PLATFORM_H
