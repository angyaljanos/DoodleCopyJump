//
// Created by jani on 2020. 04. 26..
//

#include "BluePlatform.h"
void BluePlatform::Update(){
    if(goingLeft)
        pos.x -= 1;
    else
        pos.x += 1;
}