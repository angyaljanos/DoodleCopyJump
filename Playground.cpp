//
// Created by jani on 2020. 04. 26..
//

#include "Playground.h"
#include "Platform.h"


bool Playground::CollisionCheck(Vector2D v1Pos,Vector2D v1Dims, Vector2D v2Pos,Vector2D v2Dims) {
    if (v1Pos.x + v1Dims.x >= v2Pos.x &&
        v1Pos.x <= v2Pos.x + v2Dims.x &&
        v1Pos.y + v1Dims.y >= v2Pos.y &&
        v1Pos.y <= v2Pos.y + v2Dims.x) {
        return true;
    }
    return false;
}
//unready
void Playground::initialSetup() {
    for (int i = 0; i < 15; ++i) {
        int t = rand()%10;
        if(t < 8) {
            //plats.emplace_back(Plat)
        }
    }
}
Vector2D Playground::generateRandom(double minX, double maxX, double minY, double maxY) {

    double X = ((double)rand()/RAND_MAX)*(maxX - minX) + minX;
    double Y = ((double)rand()/RAND_MAX)*(maxY - minY) + minY;
    return Vector2D(X,Y);
}

void Playground::Draw() {
    std::list<Platform*>::iterator iter;
    for (iter = plats.begin();iter != plats.end();iter++) {
        (*iter)->Draw(mainRenderer);
    }
    if(enemy != NULL)
        enemy->Draw(mainRenderer);

    doodle.Draw(mainRenderer);
}
void Playground::Update(){
    std::list<Platform*>::iterator iter;
    for (iter = plats.begin();iter != plats.end();iter++) {
        (*iter)->Update();
    }
}