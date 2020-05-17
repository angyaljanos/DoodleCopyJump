//
// Created by jani on 2020. 04. 26..
//

#include "Character.h"
#include "Playground.h"
#include "SDL_Fake.h"
#include "Enemy.h"

#include "memtrace.h"
///@brief Az ugrás maximális értékét tároló globális változó
double jumpLimit = -100;
/**@briefA karakter irányítását végző függvény.
 *
 * @param ev : A felhasználó és a számítógép között fellépő eseményeket tárolja
 * @param enemy : A játékban található ellenfél pointere: NULL ha éppen nem létezik
 * @param display : A rajzolást végző képernyő tulajdonságait/metódusait tároló osztály referenciája
 */
void Character::Control(SDL_Event& ev,Enemy* enemy,Display& display) {
        if(ev.type == SDL_KEYDOWN) {
            switch (ev.key.keysym.sym) {
                //Both hand Supported Control
                case SDLK_RIGHT:
                case SDLK_d:
                    pos.x += 10;
                    if(pos.x > display.getScreenWidth())
                        pos.x = 10 - dims.x;
                    break;
                case SDLK_LEFT:
                case SDLK_a:
                    pos.x -= 10;
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
///@briefA karakter képessége mellyel legyőzi az ellenfelét
void Character::Shoot(Enemy* enemy){
    if(enemy != NULL)
    {
        enemy->setToDead();
        enemy = NULL;
    }
}
///@brief A karakter frissítését végző függvény
void Character::Update(Display& d,Enemy* enemy) {
    pos += velocity;
    velocity += .5;
    //Ha a játékos kiesik a képernyőről a karaktere meghal
    if(pos.y > d.getScreenHeight())
        dead = true;
    // Ellenféllel való ütközéskor a játékos karaktere szintén meghal
    if((enemy != NULL) && Playground::CollisionCheck(this->pos,this->dims,
                                enemy->pos,enemy->dims))
        dead = true;
}
///@brief A karakter "él-e" tulajdonságát lekérdező függvény
bool Character::Alive() const {
    return !dead;
}
void Character::Draw(SDL_Renderer* renderer) const {

    SDL_Rect rect = {.x = (int)pos.x, .y = (int)pos.y,
                     .w = (int)dims.x,.h = (int)dims.y};
    SDL_RenderCopy(renderer,texture,NULL,&rect);

}
///@brief A karakter emelkedéséért felelős metódus
void Character::Jump(){
    velocity = -10;

}
/**@brief Vissza adja hogy a karakter esik-e
 * Ha esik igaz értékkel tér vissza, ellenben emelkedik a karakter.
 * @return
 */
bool Character::fall() const {
    return velocity > 0;
}
///@brief Beállítja a játékos pontszámát
void Character::setScore(unsigned int p) {
    score.setScore(p);
}
///@brief Visszaadja a játékos által elért pontszámot
size_t Character::getScore() const {
    return score.getScore();
}
///@brief A felhasználó
void Character::setName(const char* NewName) {
    score.setName(NewName);
}
std::string Character::getName() {
    return score.getName();
}