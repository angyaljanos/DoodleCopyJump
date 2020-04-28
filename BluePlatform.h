//
// Created by jani on 2020. 04. 26..
//

#ifndef NAGYHAZI_BLUEPLATFORM_H
#define NAGYHAZI_BLUEPLATFORM_H
#include "SDL_Fake.h"
//#include "SDL2_gfxPrimitives.h"
//#include "SDL_image.h"
//#include "SDL2/SDL_ttf.h"
#include "Platform.h"

class BluePlatform:public Platform {
private:
    static int gap;
    static int maxGap;
    bool goingLeft;

public:
    BluePlatform(Vector2D pos, SDL_Renderer* renderer, const char* PATH = "assets/greenF.png",Vector2D dims = Vector2D(58,15)):Platform(pos,renderer,PATH,dims){
        if(rand()%2 == 0)
            goingLeft = true;
        else
            goingLeft = false;
    }
    void Update();
};


#endif //NAGYHAZI_BLUEPLATFORM_H
