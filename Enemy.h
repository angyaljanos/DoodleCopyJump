//
// Created by jani on 2020. 04. 25..
//

#ifndef NAGYHAZI_ENEMY_H
#define NAGYHAZI_ENEMY_H

#include <iostream>
#include "Vector2D.h"
#include "Sprite.h"
#include "SDL_Fake.h"
#include "memtrace.h"

///Az ellenfelet deffiniáló osztály
class Enemy:public Sprite{
private:
    bool dead;
public:
    //Üres konstruktor a könnyebb pointer kezeléshez
    Enemy(){
        dead = false;
    }
    Enemy(Vector2D pos, Display& display,Vector2D dims = Vector2D(58,32), const char* PATH = "../assets/boss.png"):Sprite(pos,dims,PATH,display){
        dead = false;
        if(texture == NULL)
            std::cerr<<"Failed to load texture in Enemy class\n";
    }
    void Draw(SDL_Renderer*) const;
    void setToDead();
};
#endif //NAGYHAZI_ENEMY_H
