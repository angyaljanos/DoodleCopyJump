//
// Created by jani on 2020. 04. 24..
//

#ifndef NAGYHAZI_SCORELINE_HPP
#define NAGYHAZI_SCORELINE_HPP
#include <string>
#include <iostream>
#include "SDL_Fake.h"
#include "memtrace.h"

class ScoreLine{
    std::string name;
    size_t point;
public:
    ScoreLine(std::string& Name, size_t Point):name(Name),point(Point){}
    std::string getName() const {
        return name;
    }
    size_t getPoint() const {
        return point;
    }

};
#endif //NAGYHAZI_SCORELINE_HPP
