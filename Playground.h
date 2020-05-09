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
#include "memtrace.h"

class Playground {
private:

public:
    Playground(Display& display);

    static bool CollisionCheck(Vector2D pos1, Vector2D dims1 ,Vector2D pos2, Vector2D dims2);
    Enemy* enemy;
    std::list<Platform*> plats;
    Character doodle;


    void initialSetup(Display& display);
    void Draw(Display& d);
    double generateRandom(double minX, double maxX);
    void Update();
    void Game(Display&);

    ~Playground(){

        for (std::list<Platform*>::iterator i = plats.begin(); i!=plats.end();++i) {
            delete *i;
        }
    }
};


#endif //NAGYHAZI_PLAYGROUND_H
