//
// Created by jani on 2020. 04. 24..
//

#ifndef NAGYHAZI_VECTOR2D_H
#define NAGYHAZI_VECTOR2D_H
struct Vector2D{
    double x,y;

    Vector2D(const double x = 0, const double y = 0);
    Vector2D& operator+=(const Vector2D&);
    Vector2D& operator-=(const Vector2D&);
};
#endif //NAGYHAZI_VECTOR2D_H
