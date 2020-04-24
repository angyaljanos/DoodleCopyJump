//
// Created by jani on 2020. 04. 24..
//

#ifndef NAGYHAZI_SCORELINE_H
#define NAGYHAZI_SCORELINE_H
#include <string>
#include <iostream>

class ScoreLine{
    static std::string file;
    std::string name;
    size_t point;

public:
    ScoreLine(std::string& Name, size_t Point):name(Name),point(Point){}

    void PrintFile();
};
#endif //NAGYHAZI_SCORELINE_H
