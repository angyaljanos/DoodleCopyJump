//
// Created by jani on 2020. 04. 26..
//

#include "Character.h"
#include "Playground.h"
#include "SDL_Fake.h"
#include "Enemy.h"

#include "memtrace.h"

Vector2D charDims(58,49);
Vector2D starter(180 - 29,450);
double jumpLimit = -100;

void Character::Control(SDL_Event& ev,Enemy* enemy,Display& display) {
        if(ev.type == SDL_KEYDOWN) {
            switch (ev.key.keysym.sym) {
                //Both hand Supported Control
                case SDLK_RIGHT:
                case SDLK_d:
                    pos.x += 7;
                    if(pos.x > display.getScreenWidth())
                        pos.x = 10 - dims.x;
                    break;
                case SDLK_LEFT:
                case SDLK_a:
                    pos.x -= 7;
                    if(pos.x + dims.y < 0)
                        pos.x = display.getScreenWidth();
                    break;
                case SDLK_SPACE:
                    Shoot(enemy);
                default:
                    break;
            }
        }
}
//UnReady
void Character::Shoot(Enemy* enemy){
    if(enemy != NULL)
    {
        enemy = NULL;
    }
}
void Character::Update(Display& d) {
    pos += velocity;
    velocity += .5;
    if(pos.y > d.getScreenHeight())
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
void Character::Kill() {
    dead = true;
}
void Character::Jump(){
    velocity = -10;

}
bool Character::fall() const {
    return velocity > 0;
}
void Character::setScore(size_t p) {
    score.setScore(p);
}
size_t Character::getScore() const {
    return score.getScore();
}