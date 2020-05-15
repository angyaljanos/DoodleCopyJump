//
// Created by jani on 2020. 04. 25..
//

#ifndef NAGYHAZI_ENEMY_H
#define NAGYHAZI_ENEMY_H

#include <iostream>
#include "Vector2D.h"
#include "Sprite.h"
#include "SDL_Fake.h"
//#include "SDL2_gfxPrimitives.h"
//#include "SDL_image.h"
//#include "SDL2/SDL_ttf.h"
#include "memtrace.h"

class Enemy:public Sprite{
private:
    bool dead;
public:
    Enemy(){
        dead = false;
    }
    Enemy(Vector2D& pos,Vector2D& dims, const char* PATH, SDL_Renderer* renderer):Sprite(pos,dims,PATH,renderer){
        dead = false;
        if(texture == NULL)
            std::cerr<<"Failed to load texture in Enemy class\n";
    }
    Enemy(double x, double y,double w, double h, const char* PATH, SDL_Renderer* renderer):Sprite(Vector2D(x,y),Vector2D(w,h),PATH,renderer){
        dead = false;
    }
    void Update();
    void Draw(SDL_Renderer*) const;
    void getKilled(bool);
};
#endif //NAGYHAZI_ENEMY_H
