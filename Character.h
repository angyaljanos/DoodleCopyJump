//
// Created by jani on 2020. 04. 26..
//

#ifndef NAGYHAZI_CHARACTER_H
#define NAGYHAZI_CHARACTER_H

#include "Sprite.h"

class Character:public Sprite {
private:
    bool dead = false;
    void Control(bool);
public:
    Character(Vector2D& pos,Vector2D& dims, const char* PATH, SDL_Renderer* renderer):Sprite(pos,dims,PATH,renderer){
        dead = false;
        if(texture == NULL)
            std::cerr<<"Failed to load texture in Character class\n";
    }
    Character(double x, double y,double w, double h, const char* PATH, SDL_Renderer* renderer):Sprite(Vector2D(x,y),Vector2D(w,h),PATH,renderer){
        dead = false;
    }
    void Draw(SDL_Renderer*) const;
    void Update();
};


#endif //NAGYHAZI_CHARACTER_H
