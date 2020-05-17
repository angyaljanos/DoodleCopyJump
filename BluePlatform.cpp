//
// Created by jani on 2020. 04. 26..
//
#include "SDL_Fake.h"
#include "BluePlatform.h"
#include "memtrace.h"
/**@brief A Kék Platformok viselkedését leíró függvény.
 * Frissíti a platformok aktuális helyzetét, illetve ellernőrzi ha kiléptek képernyőről.
 * @param c A játékos által írányított karakter osztály referenciája(Pontosabb magyarázat a WhitePlatform résznél olvasható)
 * @param display: A képernyő tulajdonságait illetve metódusait tároló osztály;
 */
void BluePlatform::Update(Character& c,Display& display){
    if(goingLeft) {
        pos.x -= 3;
        if((pos.x + dims.x) < 0)
            pos.x = display.getScreenWidth();
    }
    else {
        pos.x += 3;
        if(pos.x > display.getScreenWidth())
            pos.x = 0;
    }
}