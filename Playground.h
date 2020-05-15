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
    double random(double minX, double maxX);
    void Update(Display& display);
    void Game(Display&);
    void drawScore(Display&d) const;

    inline Platform* generateNew(Vector2D,Display& p);

    template <class T>
    bool deletePlats(T predicate);

    ~Playground();
};


//Functors for deleting
struct OutOfScreen{
    const Display& d;
    OutOfScreen(const Display& d):d(d){

    }
    bool operator()(Vector2D v){
        return v.y > this->d.getScreenHeight();
    }
};
struct All{
    bool operator()(Vector2D v){
        return true;
    }
};


#endif //NAGYHAZI_PLAYGROUND_H
