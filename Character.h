//
// Created by jani on 2020. 04. 26..
//

#ifndef NAGYHAZI_CHARACTER_H
#define NAGYHAZI_CHARACTER_H

#include "Sprite.h"
#include "Enemy.h"
#include "Display.h"
#include "SDL_Fake.h"
#include "Display.h"
#include "ScoreLine.hpp"
#include "memtrace.h"


extern Vector2D starter;
extern Vector2D charDims;
extern double jumpLimit;

class Character:public Sprite {
private:
    bool dead;
    double velocity;
    bool falling;
    ScoreLine score;
    void Shoot(Enemy* enemy);

public:
    Character( SDL_Renderer* renderer,Vector2D& dims = charDims,Vector2D& pos = starter, const char* PATH = "../assets/doodle.png"):Sprite(pos,dims,PATH,renderer){
        dead = false;
        velocity = 10;
        if(texture == NULL)
            std::cerr<<"Failed to load texture in Character class\n";
    }
    void Control(SDL_Event& ev,Enemy* enemy,Display& display);
    void Draw(SDL_Renderer*) const;
    void Update(Display& d);
    bool Alive()const;
    void Kill();
    void Jump();
    bool fall() const;
    void setScore(size_t);
    size_t getScore() const;
};


#endif //NAGYHAZI_CHARACTER_H
