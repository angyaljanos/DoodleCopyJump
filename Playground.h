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
    /// A játék elemeinek(platformok,karakter,ellenfél..) megjelenítése
    void Draw(Display& d);
    ///@brief Véletlenszám generátor
    double random(double minX, double maxX);
    ///@brief A játék elemeinek frissítése
    void Update(Display& display);
    /**A Playground vezérlő függvénye: ez felelős a többi függvény meghívásáért.
     *
     * @param fm -FileManager amely kezeli azt a fájlt amelybe a játékos eredméynét és elért pontszámát menteni szeretnénk
     */
    void Game(Display&,FileManager& fm);
    ///@brief A játékban elért pontszám megjelenítése a kijelzőn
    void drawScore(Display&d) const;
    ///@brief A "Game Over" felirat megjelenítéséért és a játékos nevének bekééréért felelő metódus
    void gameOver(Display &d);
    ///@brief Ha éppen nincs ellenfél a pályán akkor a függvény egy véletlenszerű szám generálásával eldönti hogy a valamely platformon lessz e
    void makeEnemy(Display& d);
    ///@brief A "plats" lista építéért felelős függvény
    inline Platform* generateNew(Vector2D,Display& p);

    ///@brief A paraméterként kapott feltétel szerint törli azokat platformokat amellyek eleget tesznek a feltételnek
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
