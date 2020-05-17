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
#include "FileManager.h"
#include "SDL_Fake.h"
#include "memtrace.h"

/**@brief A játék lebonyolításáért felelős osztály.
 *
 * Úgymondd a program szempontjából "Játszótér"
 */
class Playground {
private:
    Vector2D last,current;
public:
    Playground(Display& display);
    ///@brief Ütközés ellenőrzés 2 darab négyzetre
    static bool CollisionCheck(Vector2D pos1, Vector2D dims1 ,Vector2D pos2, Vector2D dims2);
    Enemy* enemy;
    std::list<Platform*> plats;
    Character doodle;

    ///@brief A Játék kezdeti állapotát beállító függvény
    void initialSetup(Display& display);
    void Draw(Display& d);
    double random(double minX, double maxX);
    void Update(Display& display);
    void Game(Display&,FileManager& fm);
    void drawScore(Display&d) const;
    void gameOver(Display &d);
    void makeEnemy(Display& d);
    inline Platform* generateNew(Vector2D,Display& p);

    template <class T>
    bool deletePlats(T predicate);

    ~Playground();
};

/**@brief Funktorok a Playground-ban deffiniált deletePlats-függvényhez
 * Az All az összes platformot törli,
 * Az OutOfScreen pedig azokat amelyek már kisüllyedtek a képernyőből
 */

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
