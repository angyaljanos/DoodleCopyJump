//
// Created by jani on 2020. 04. 26..
//
#include "BluePlatform.h"
#include "Playground.h"
#include "Platform.h"
#include "SDL_Fake.h"
#include "WhitePlatform.h"
#include "memtrace.h"


Vector2D last,current;
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
        Vector2D tmp = Playground::generateRandom(0, display.getScreenWidth() - Platform::platWidth);
        tmp.y = (i*Platform::platHeight) + (i-1) * Platform::gap;
        if(chance < 8) {
            p = new Platform(tmp, display.renderer);
        }
        else if(chance == 8){
            p = new BluePlatform(tmp, display.renderer);
        }
        else if(chance == 9){
            p = new WhitePlatform(tmp, display.renderer);
        }
        std::cout<< i <<" X:"<<p->pos.x <<" Y:"<<p->pos.y<<std::endl;
        plats.emplace_back(p);

    }
    plats.emplace_back(new Platform(Vector2D(display.getScreenWidth()/2 - doodle.dims.y/2,550),display.renderer));
    enemy = NULL;
}

double Playground::generateRandom(double minX, double maxX) {
    double X = ((double)rand()/RAND_MAX)*(maxX - minX) + minX;
    return X;
}

void Playground::Draw(Display& d) {
    //std::vector<Sprite*> sprites;
    //sprites.insert(sprites.end(),plats.begin(),plats.end());
    //sprites.push_back(&doodle);
    //sprites.push_back(enemy);
    SDL_RenderClear(d.renderer);
    d.drawBG();
    for (std::list<Platform*>::iterator iter = plats.begin(); iter != plats.end();iter++) {
        if(*iter != NULL)
            (*iter)->Draw(d.renderer);
    }
    doodle.Draw(d.renderer);
    if(enemy != NULL)
        enemy->Draw(d.renderer);
}

void Playground::Update(){
    std::list<Platform*>::iterator iter;
    last = current;

    for (iter = plats.begin();iter != plats.end();iter++) {
        (*iter)->Update(doodle);
        //jump - collision check
        if(Playground::CollisionCheck(doodle.pos,doodle.dims,
                                        (*iter)->pos,      (*iter)->dims) && doodle.fall())
        {
            doodle.Jump();
            std::cout<<"MOST"<<std::endl;
            current = (*iter)->pos;
        }
    }
    double sink = last.y - current.y;

    doodle.Update();
    if(enemy != NULL)
        enemy->Update(sink);


}
void Playground::Game(Display& display) {
    SDL_RenderClear(display.renderer);
    SDL_Event event;
    bool moving = false;
    while (SDL_WaitEvent(&event) && doodle.Alive()) {
        if(event.type == SDL_KEYDOWN){
            doodle.Control(event,enemy);
        }

        if(event.type == SDL_USEREVENT){
            Draw(display);
            SDL_RenderPresent(display.renderer);
            Update();
            continue;
        }
        //Mid Game Quit
        if( event.type == SDL_QUIT) {
            return;
        }
    }
}