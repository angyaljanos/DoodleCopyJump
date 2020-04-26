//
// Created by jani on 2020. 04. 26..
//

#ifndef NAGYHAZI_PLAYGROUND_H
#define NAGYHAZI_PLAYGROUND_H

#include "Vector2D.h"
#include "Enemy.h"
#include <iostream>
class Playground {
public:
    static bool CollisionCheck(Vector2D, Vector2D,Vector2D, Vector2D);
    static Enemy* enemy;
};


#endif //NAGYHAZI_PLAYGROUND_H
