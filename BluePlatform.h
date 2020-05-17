//
// Created by jani on 2020. 04. 26..
//

#ifndef NAGYHAZI_BLUEPLATFORM_H
#define NAGYHAZI_BLUEPLATFORM_H
#include "SDL_Fake.h"
//#include "SDL2_gfxPrimitives.h"
//#include "SDL_image.h"
//#include "SDL2/SDL_ttf.h"
#include "Platform.h"
#include "memtrace.h"
///@brief A KÉK platformok osztálya, az ős osztálly objektumaival ellentétben az ehhez tartozó objektumok vízszintesen mozognak
class BluePlatform:public Platform {
private:
    ///@brief Két platform között lévő függöleges távolság, az idő elteltével növekszik míg el nem éri a maximumát
    static int gap;
    ///@briefA platformok függőleges távolságának felső határa
    static int maxGap;
    /**@brief A platform mozgásának iránynát tároló logikai változó.
     * Ha az értéke igaz akkor a platform balra halad, hamis esetén pedig jobbra
     */
    bool goingLeft;

public:
    //Két paraméterrel hívható konstruktor: Pozíció és Display referenciával hivatkozható
    BluePlatform(Vector2D pos, Display& display, const char* PATH = "assets/blue.png",Vector2D dims = Vector2D(58,15)):Platform(pos,display,PATH,dims){
        goingLeft = rand()%2==0;
        //Az üres textúra esetén kivétel dobás a melyett a main függvény catch ága kap el
        if(texture == NULL)
            throw std::logic_error("Üres textúra @ BluePlatform");
    }
    void Update(Character& c,Display& display);
};


#endif //NAGYHAZI_BLUEPLATFORM_H
