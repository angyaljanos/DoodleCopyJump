//
// Created by jani on 2020. 04. 24..
//

#ifndef NAGYHAZI_VECTOR2D_H
#define NAGYHAZI_VECTOR2D_H

#include <iostream>
#include "SDL_Fake.h"
#include "memtrace.h"
struct Vector2D{
    double x,y;

    Vector2D(const double x = 0, const double y = 0);

    ///Vector +- Vector
    Vector2D& operator+=(const Vector2D&);
    Vector2D& operator-=(const Vector2D&);

    ///Vector +- double
    ///vertical vector komponent modification
    Vector2D operator+(const double);
    Vector2D operator-(const double);

    ///Vector += double
    Vector2D& operator+=(double);

};

///Vector + double
///vertical vector komponent modification


#endif //NAGYHAZI_VECTOR2D_H
