//
// Created by jani on 2020. 04. 24..
//
#include <string>
#include <iostream>
#include <fstream>
#include "ScoreLine.h"
std::string ScoreLine::file = "Scores.txt";

void ScoreLine::PrintFile() {
    std::ofstream myfile;
    myfile.open (ScoreLine::file);
    myfile << this->name <<";"<< this->point<<"\n";
    myfile.close();
}
