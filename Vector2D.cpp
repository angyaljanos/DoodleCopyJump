//
// Created by jani on 2020. 04. 24..
//
#include "Vector2D.h"
#include "SDL_Fake.h"

Vector2D::Vector2D(const double x, const double y) {
    this->x = x;
    this->y = y;
}
Vector2D& Vector2D::operator+=(const Vector2D& v) {
    this->x += v.x;
    this->y += v.y;
    return *this;
}
Vector2D& Vector2D::operator-=(const Vector2D& v) {
    this->x -= v.x;
    this->y -= v.y;
    return *this;
}
Vector2D Vector2D::operator+(const double num) {
    return Vector2D(this->x,this->y+num);
}

Vector2D Vector2D::operator-(const double num) {
    return Vector2D(this->x,this->y -num);
}

Vector2D operator+=(double num, const Vector2D& v){
    return Vector2D(v.x,v.y+num);
}
