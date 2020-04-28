//
// Created by jani on 2020. 04. 26..
//

#ifndef NAGYHAZI_PLAYGROUND_H
#define NAGYHAZI_PLAYGROUND_H

#include <list>
#include "Vector2D.h"
#include "Enemy.h"
#include <iostream>
#include "Platform.h"
#include "Character.h"
#include "SDL_Fake.h"

class Playground {
private:
    SDL_Renderer* mainRenderer;
    SDL_TimerID  timerId;
public:

    Playground(){
        //timerId = SDL_AddTimer(1000/240, this->Update(), this);
    }

    static bool CollisionCheck(Vector2D pos1, Vector2D dims1 ,Vector2D pos2, Vector2D dims2);
    static Enemy* enemy;
    std::list<Platform*> plats;
    Character doodle;


    void initialSetup(Display& d);
    void Draw();
    Vector2D generateRandom(double minX, double maxX, double miny, double maxY);
    void Update(Character& c);
    void Game();

    ~Playground(){
        SDL_RemoveTimer(timerId);
    }
};


#endif //NAGYHAZI_PLAYGROUND_H
