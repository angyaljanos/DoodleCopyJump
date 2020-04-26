//
// Created by jani on 2020. 04. 26..
//

#include "Character.h"
#include "Playground.h"
#include "Display.h"

void Character::Control(bool keyPressed) {
    if(keyPressed){
        SDL_Event* ev;
        SDL_PollEvent(ev);
        if(ev->type == SDL_KEYDOWN){
            switch (ev->key.keysym.sym){
                //Both hand Supported Control
                case SDLK_RIGHT:
                case SDLK_d:
                    pos.x += 3;
                    break;
                case SDLK_LEFT:
                case SDLK_a:
                    pos.x -= 3;
                    break;
                case SDLK_SPACE:
                    Shoot();
                default:break;
            }
        }
    }
}
//UnReady
void Character::Shoot(){
    if(Playground::enemy != NULL)
    {

    }
}void Character::Update(Enemy* en, Display& display) {
    if(Playground::CollisionCheck(en->pos,en->dims,this->pos,this->dims)
        || this->pos.y > display.getScreenHeight())
        dead = true;

}
bool Character::Alive() const {
    return !dead;
}
void Character::Draw(SDL_Renderer* renderer) const {

    SDL_Rect rect = {.x = (int)pos.x, .y = (int)pos.y,
                     .w = (int)dims.x,.h = (int)dims.y};
    SDL_RenderCopy(renderer,texture,NULL,&rect);

}