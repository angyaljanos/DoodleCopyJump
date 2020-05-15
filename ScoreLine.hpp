//
// Created by jani on 2020. 04. 24..
//

#ifndef NAGYHAZI_SCORELINE_HPP
#define NAGYHAZI_SCORELINE_HPP
#include <string>
#include <iostream>
#include "SDL_Fake.h"
#include "memtrace.h"

class ScoreLine : public std::error_code {
    std::string name;
    size_t point;
public:
    ScoreLine(std::string Name = "", size_t Point = 0):name(Name),point(Point){

    }
    ScoreLine(const char* line){
        std::stringstream linestream(line);
        std::getline(linestream,this->name,';');
        linestream>>point;
    }
    std::string getName() const {
        return name;
    }
    size_t getScore() const {
        return point;
    }
    void setScore(size_t s){
        point = s;
    }
    void setName(std::string string){
        name = string;
    }
    bool operator<(const ScoreLine& other){
        return this->point < other.getScore();
    }
    std::string ToString(){
        return (std::string(name + ";")+std::to_string(point));
    }

};
#endif //NAGYHAZI_SCORELINE_HPP
