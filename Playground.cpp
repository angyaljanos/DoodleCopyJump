//
// Created by jani on 2020. 04. 26..
//
#include <iostream>
#include "BluePlatform.h"
#include "Playground.h"
#include "Platform.h"
#include "SDL_Fake.h"
#include "WhitePlatform.h"
#include "memtrace.h"
#include "ScoreLine.hpp"
#include "FileManager.h"
#include <cstring>



Playground::Playground(Display& display):doodle(display){
    initialSetup(display);
}

//source:   https://infoc.eet.bme.hu/sdl/
bool input_text(char *dest, size_t hossz, SDL_Rect teglalap, SDL_Color hatter, SDL_Color szoveg, SDL_Renderer *renderer, TTF_Font *font) {

    char composition[SDL_TEXTEDITINGEVENT_TEXT_SIZE];
    composition[0] = '\0';

    char textandcomposition[hossz + SDL_TEXTEDITINGEVENT_TEXT_SIZE + 1];
    int maxw = teglalap.w - 2;
    int maxh = teglalap.h - 2;

    dest[0] = '\0';

    bool enter = false;
    bool kilep = false;

    SDL_StartTextInput();
    while (!kilep && !enter) {

        boxRGBA(renderer, teglalap.x, teglalap.y, teglalap.x + teglalap.w - 1, teglalap.y + teglalap.h - 1, hatter.r, hatter.g, hatter.b, 255);
        rectangleRGBA(renderer, teglalap.x, teglalap.y, teglalap.x + teglalap.w - 1, teglalap.y + teglalap.h - 1, szoveg.r, szoveg.g, szoveg.b, 255);

        int w;
        strcpy(textandcomposition, dest);
        strcat(textandcomposition, composition);
        if (textandcomposition[0] != '\0') {
            SDL_Surface *felirat = TTF_RenderUTF8_Blended(font, textandcomposition, szoveg);
            SDL_Texture *felirat_t = SDL_CreateTextureFromSurface(renderer, felirat);
            SDL_Rect cel = { teglalap.x, teglalap.y, felirat->w < maxw ? felirat->w : maxw, felirat->h < maxh ? felirat->h : maxh };
            SDL_RenderCopy(renderer, felirat_t, NULL, &cel);
            SDL_FreeSurface(felirat);
            SDL_DestroyTexture(felirat_t);
            w = cel.w;
        } else {
            w = 0;
        }
        /* kurzor kirajzolasa */
        if (w < maxw) {
            vlineRGBA(renderer, teglalap.x + w + 2, teglalap.y + 2, teglalap.y + teglalap.h - 3, szoveg.r, szoveg.g, szoveg.b, 192);
        }
        SDL_RenderPresent(renderer);

        SDL_Event event;
        SDL_WaitEvent(&event);
        switch (event.type) {
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_BACKSPACE) {
                    int textlen = strlen(dest);
                    do {
                        if (textlen == 0) {
                            break;
                        }
                        if ((dest[textlen-1] & 0x80) == 0x00)   {
                            /* Egy bajt */
                            dest[textlen-1] = 0x00;
                            break;
                        }
                        if ((dest[textlen-1] & 0xC0) == 0x80) {
                            dest[textlen-1] = 0x00;
                            textlen--;
                        }
                        if ((dest[textlen-1] & 0xC0) == 0xC0) {
                            dest[textlen-1] = 0x00;
                            break;
                        }
                    } while(true);
                }
                if (event.key.keysym.sym == SDLK_RETURN) {
                    enter = true;
                }
                break;

            case SDL_TEXTINPUT:
                if (strlen(dest) + strlen(event.text.text) < hossz) {
                    strcat(dest, event.text.text);
                }

                composition[0] = '\0';
                break;

            case SDL_TEXTEDITING:
                strcpy(composition, event.edit.text);
                break;

            case SDL_QUIT:
                SDL_PushEvent(&event);
                kilep = true;
                break;
            default:
                break;
        }
    }

    SDL_StopTextInput();
    return enter;
}

bool Playground::CollisionCheck(Vector2D v1Pos,Vector2D v1Dims, Vector2D v2Pos,Vector2D v2Dims) {
    return v1Pos.x + v1Dims.x >= v2Pos.x &&
           v1Pos.x <= v2Pos.x + v2Dims.x &&
           v1Pos.y + v1Dims.y >= v2Pos.y &&
           v1Pos.y <= v2Pos.y + v2Dims.y;
}

void Playground::gameOver(Display &d) {
    SDL_Rect drawingRect = {.x = 20,.y = 30,.w = (d.getScreenWidth() - 40),.h = 50};
    SDL_Surface* surface = TTF_RenderUTF8_Blended(d.getFont(),"Game Over",{0,0,0,255});
    SDL_Texture* texture = SDL_CreateTextureFromSurface(d.renderer,surface);

    SDL_RenderCopy(d.renderer,texture,NULL,&drawingRect);

    SDL_Rect writingRect = drawingRect;
    writingRect.y += 55;
    SDL_Color Bg = {255,255,255,55};
    SDL_Color black = {0,0,0,155};
    char username[16] = "NamelessUser";
    input_text(username,16,writingRect,Bg,black,d.renderer,d.getFont());
    doodle.setName(username);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

void Playground::makeEnemy(Display& d) {
    std::list<Platform*>::iterator iter;
    int randomChance = random(0,99);
    for (iter = plats.begin(); iter != plats.end();iter++) {
        if((*iter)->pos.y < 0 &&
            randomChance <= 1 &&
            enemy == NULL){
            enemy = new Enemy(((*iter)->pos),d);
            enemy->pos -= enemy->dims.y;
            std::cout<<"Enemy has been appeared"<<std::endl;
        }
    }
}

void Playground::initialSetup(Display& display) {
    for (size_t i = 0; i * (Platform::platHeight +Platform::gap) < (int)display.getScreenHeight() + 10 ; ++i) {
        int chance = rand() % 10;
        Platform* p;
        Vector2D tmp = Playground::random(0, display.getScreenWidth() - Platform::platWidth);
        tmp.y = (i*Platform::platHeight) + (double)(i-1) * Platform::gap;
        if(chance < 8) {
            p = new Platform(tmp, display);

        }
        else if(chance == 8){
            p = new BluePlatform(tmp, display);

        }
        else if(chance == 9){
            p = new WhitePlatform(tmp, display);

        }
        //std::cout<< i <<" X:"<<p->pos.x <<" Y:"<<p->pos.y<<std::endl;
        plats.emplace_back(p);
        //delete p;
    }
    plats.emplace_back(new Platform(Vector2D(display.getScreenWidth()/2 - doodle.dims.y/2,550),display));
    enemy = NULL;

}

// Random Number Generator - just how i like it
double Playground::random(double minX, double maxX) {
    double X = ((double)rand()/RAND_MAX)*(maxX - minX) + minX;
    return X;
}

inline Platform* Playground::generateNew(Vector2D newPos,Display& display) {
    int r = random(1,10);
    Platform* tmp;
    if(r < 7)
        tmp = new Platform(newPos,display);
    else if(r < 9)
        tmp = new BluePlatform(newPos,display);
    else
        tmp = new WhitePlatform(newPos,display);

    tmp->pos.x = random(0, display.getScreenWidth() - Platform::platWidth);
    return tmp;
}

template<class T>
bool Playground::deletePlats(T predicate) {
    for (std::list<Platform*>::iterator iter = plats.begin();iter != plats.end();iter++) {
        if(predicate((*iter)->pos)){
            delete *iter;
            plats.remove(*iter);
            return true;
        }
    }
    //std::cout<<plats.size()<<std::endl;
    return false;
}

Playground::~Playground() {
    while(!plats.empty())
        deletePlats(All());
    if(enemy != NULL)
        delete enemy;
}

void Playground::Draw(Display& d) {
    SDL_RenderClear(d.renderer);
    d.drawBG();
    for (std::list<Platform*>::iterator iter = plats.begin(); iter != plats.end();iter++) {
        if((*iter) != NULL)
            (*iter)->Draw(d.renderer);
    }
    doodle.Draw(d.renderer);
    if(enemy != NULL && (enemy->pos.y + enemy->dims.y) > 0)
        enemy->Draw(d.renderer);
    drawScore(d);
}

void Playground::drawScore(Display &d) const {
    SDL_Color col = {0,0,0,150};
    SDL_Rect scoreRect = {.x = 0,.y = 0,.w = 100, .h = 50};
    std::stringstream stream;
    stream << "Score: " << doodle.getScore() << std::endl;
    SDL_Surface* surface = TTF_RenderUTF8_Blended(d.getFont(),stream.str().c_str(),col);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(d.renderer,surface);

    std::cout<<stream.str()<<std::endl;
    SDL_RenderCopy(d.renderer,texture,NULL,&scoreRect);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

void Playground::Update(Display& display){
    std::list<Platform*>::iterator iter;

    //std::cout<<"Before sink"<<std::endl;
    last = current;
    for (iter = plats.begin();iter != plats.end();iter++) {
        (*iter)->Update(doodle,display);
        //jump - collision check
        if(Playground::CollisionCheck(doodle.pos,doodle.dims,
                                        (*iter)->pos,(*iter)->dims)
                                        && doodle.fall())
        {
            current = (*iter)->pos;
            if(current.y < last.y)
                doodle.setScore(doodle.getScore() + int((current.y - last.y)*-1));
            doodle.Jump();
            if(WhitePlatform* test = dynamic_cast<WhitePlatform*>(*iter))
            {
                test->setAsUsed();
                plats.remove(*iter);
                return;
            }
        }
    }

    doodle.Update(display,enemy);

    if(doodle.pos.y + doodle.dims.y < display.getScreenHeight()/3){
        //std::cout<<"After sink"<<std::endl;
        for (iter = plats.begin();iter != plats.end();iter++) {
            //Extend the Update Function
            (*iter)->pos += 10;
            //std::cout<<(*iter)->pos.y<<std::endl;
        }
        if(enemy != NULL)
        {
            enemy->pos+=10;
        }
    }
    OutOfScreen outOfScreen(display);

    if(deletePlats(outOfScreen)){
        plats.push_front(generateNew(plats.front()->pos - Platform::gap,display));
        makeEnemy(display);
        Platform::incraseGap();
    }
}
void Playground::Game(Display& display,FileManager& fileManager) {
    SDL_RenderClear(display.renderer);
    SDL_Event event;
    ScoreLine score;
    
    while (SDL_WaitEvent(&event) && doodle.Alive()) {
        if(event.type == SDL_KEYDOWN){
            doodle.Control(event,enemy,display);
        }

        if(event.type == SDL_USEREVENT){
            Draw(display);
            SDL_RenderPresent(display.renderer);
            if(doodle.Alive()) {
                Update(display);
            }
            continue;
        }
        //Mid-Game Quit
        if( event.type == SDL_QUIT) {
            return;
        }
    }
    if(!doodle.Alive()){
        gameOver(display);
        SDL_RenderPresent(display.renderer);
        if(doodle.getName().size() < 1){
            doodle.setName("Nameless");
        }
        fileManager.SaveRecord(doodle.score);
    }
}