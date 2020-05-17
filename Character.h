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

extern double jumpLimit;
///@brief A Játékos által írányított karakter metódusait és adattagjait tároló osztály
class Character:public Sprite {
private:
    bool dead;
    double velocity;
    void Shoot(Enemy* enemy);

public:
    ScoreLine score;
    Character( Display& display,Vector2D dims = Vector2D(36,36),Vector2D pos = Vector2D(180 - 29,450), const char* PATH = "../assets/doodle.png"):Sprite(pos,dims,PATH,display){
        dead = false;
        velocity = 10;
        score = ScoreLine("NameLess",0);
        //A textúra vizsgálata
        if(texture == NULL)
            throw std::logic_error("Failed to load texture in Character class\n");
    }
    void Control(SDL_Event& ev,Enemy* enemy,Display& display);
    void Draw(SDL_Renderer*) const;
    void Update(Display& d,Enemy* enemy);
    bool Alive()const;
    void Jump();
    bool fall() const;
    void setScore(unsigned int);
    void setName(const char*);
    size_t getScore() const;
    std::string getName();
};


#endif //NAGYHAZI_CHARACTER_H
