//
// Created by jani on 2020. 04. 26..
//
#include "BluePlatform.h"
#include "Playground.h"
#include "Platform.h"
#include "SDL_Fake.h"
#include "WhitePlatform.h"
#include "memtrace.h"
#include "ScoreLine.hpp"
#include "FileManager.h"

Playground::Playground(Display& display):doodle(display.renderer){
    initialSetup(display);
}

bool Playground::CollisionCheck(Vector2D v1Pos,Vector2D v1Dims, Vector2D v2Pos,Vector2D v2Dims) {
    return v1Pos.x + v1Dims.x >= v2Pos.x &&
           v1Pos.x <= v2Pos.x + v2Dims.x &&
           v1Pos.y + v1Dims.y >= v2Pos.y &&
           v1Pos.y <= v2Pos.y + v2Dims.y;
}

void Playground::initialSetup(Display& display) {
    for (int i = 0; i * (Platform::platHeight +Platform::gap) < (int)display.getScreenHeight() ; ++i) {
        int chance = rand() % 10;
        Platform* p;
        Vector2D tmp = Playground::random(0, display.getScreenWidth() - Platform::platWidth);
        tmp.y = (i*Platform::platHeight) + (i-1) * Platform::gap;
        if(chance < 8) {
            p = new Platform(tmp, display.renderer);
            std::cout<<"Standard at "<<i<<std::endl;
        }
        else if(chance == 8){
            p = new BluePlatform(tmp, display.renderer);
            std::cout<<"Blue at "<<i<<std::endl;
        }
        else if(chance == 9){
            p = new WhitePlatform(tmp, display.renderer);
            std::cout<<"White at "<<i<<std::endl;
        }
        //std::cout<< i <<" X:"<<p->pos.x <<" Y:"<<p->pos.y<<std::endl;
        plats.emplace_back(p);

    }
    plats.emplace_back(new Platform(Vector2D(display.getScreenWidth()/2 - doodle.dims.y/2,550),display.renderer));
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
        tmp = new Platform(newPos,display.renderer);
    else if(r < 9)
        tmp = new BluePlatform(newPos,display.renderer);
    else if(r == 9)
        tmp = new WhitePlatform(newPos,display.renderer);

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
}

void Playground::Draw(Display& d) {
    SDL_RenderClear(d.renderer);
    d.drawBG();
    for (std::list<Platform*>::iterator iter = plats.begin(); iter != plats.end();iter++) {
        if((*iter) != NULL)
            (*iter)->Draw(d.renderer);
    }
    doodle.Draw(d.renderer);
    if(enemy != NULL)
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
}

void Playground::Update(Display& display){
    std::list<Platform*>::iterator iter;

    //std::cout<<"Before sink"<<std::endl;
    for (iter = plats.begin();iter != plats.end();iter++) {
        (*iter)->Update(doodle);
        //jump - collision check
        if(Playground::CollisionCheck(doodle.pos,doodle.dims,
                                        (*iter)->pos,      (*iter)->dims) && doodle.fall())
        {
            doodle.Jump();
            //std::cout<<"MOST"<<std::endl;
        }
        //std::cout<<(*iter)->pos.y<<std::endl;
    }

    doodle.Update(display);
    if(enemy != NULL)
        enemy->Update();

    if(doodle.pos.y + doodle.dims.y < display.getScreenHeight()/3){
        //std::cout<<"After sink"<<std::endl;
        for (iter = plats.begin();iter != plats.end();iter++) {
            //Extend the Update Function
            (*iter)->pos += 10;

            //std::cout<<(*iter)->pos.y<<std::endl;
        }
    }
    OutOfScreen outOfScreen(display);

    if(deletePlats(outOfScreen)){
        plats.push_front(generateNew(plats.front()->pos - Platform::gap,display));
        Platform::incraseGap();
    }

    //std::cout<<plats.size()<<std::endl;
}
void Playground::Game(Display& display) {
    SDL_RenderClear(display.renderer);
    SDL_Event event;
    ScoreLine score;
    bool moving = false;
    while (SDL_WaitEvent(&event)) {
        if(event.type == SDL_KEYDOWN){
            doodle.Control(event,enemy,display);
        }

        if(event.type == SDL_USEREVENT){
            Draw(display);
            SDL_RenderPresent(display.renderer);
            if(doodle.Alive())
                Update(display);
            continue;
        }
        //Mid Game Quit
        if( event.type == SDL_QUIT) {
            return;
        }
    }
}