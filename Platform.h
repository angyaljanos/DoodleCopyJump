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
///@brief A játék elindítása után a képernyőn megjelenő ZÖLD felületek(platformok) megjelenítéséért és viselkedésének leításáért felelős osztály
class Platform:public Sprite{
public:
    //platform properties - all of them has the same
    static double platHeight;
    static double platWidth;
    static int gap;
    static int maxGap;

    Platform(Vector2D pos, Display& display, const char* PATH = "assets/green.png",Vector2D dims = Vector2D(58,15)):Sprite(pos,dims,PATH,display){
        if(texture == NULL)
            throw std::logic_error("Üres textúra @ Platform");
    }
    ///@brief platformok közötti távolságot növeli a megadott maximális értékig
    static void incraseGap(){
        if(Platform::gap < Platform::maxGap)
            gap+=5;
    }
    ///@brief A platformok megjelenítéséért felelős metódus
    virtual void Draw(SDL_Renderer* renderer) const;
    virtual void Update(Character& c,Display& display);
    virtual ~Platform(){}
};
#endif //NAGYHAZI_PLATFORM_H
