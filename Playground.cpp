//
// Created by jani on 2020. 04. 26..
//

#include "Playground.h"

bool Playground::CollisionCheck(Vector2D v1Pos,Vector2D v1Dims, Vector2D v2Pos,Vector2D v2Dims) {
    if (v1Pos.x + v1Dims.x >= v2Pos.x &&
        v1Pos.x <= v2Pos.x + v2Dims.x &&
        v1Pos.y + v1Dims.y >= v2Pos.y &&
        v1Pos.y <= v2Pos.y + v2Dims.x) {
        return true;
    }
    return false;
}