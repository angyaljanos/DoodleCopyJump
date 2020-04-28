//
// Created by jani on 2020. 04. 26..
//

#ifndef NAGYHAZI_WHITEPLATFORM_H
#define NAGYHAZI_WHITEPLATFORM_H

#include "Platform.h"
#include "SDL_Fake.h"

class WhitePlatform:public Platform {
private:
    bool used;
public:
    WhitePlatform(Vector2D pos, SDL_Renderer* renderer, const char* PATH = "assets/greenF.png",Vector2D dims = Vector2D(58,15)):Platform(pos,renderer,PATH,dims){
        used = false;
    }
    void Draw(SDL_Renderer* renderer);
    void Update(Character& c);
};


#endif //NAGYHAZI_WHITEPLATFORM_H
