//
// Created by jani on 2020. 04. 26..
//

#ifndef NAGYHAZI_WHITEPLATFORM_H
#define NAGYHAZI_WHITEPLATFORM_H

#include "Platform.h"
#include "SDL_Fake.h"
#include "memtrace.h"

class WhitePlatform:public Platform {
private:
    bool used;
public:
    WhitePlatform(Vector2D pos, Display& d, const char* PATH = "../assets/green.png",Vector2D dims = Vector2D(58,15)):Platform(pos,d,PATH,dims){
        used = false;
        if(texture == NULL)
            throw std::logic_error("Üres textúra @ WhitePlatform");
    }
    void Draw(SDL_Renderer* renderer);
    void Update(Character& c);
    void setAsUsed();
};


#endif //NAGYHAZI_WHITEPLATFORM_H
