//
// Created by jani on 2020. 04. 27..
//
#include <iostream>
#include <fstream>
#include <list>
#include "FileManager.h"
#include "ScoreLine.hpp"

std::string FileManager::file = "Scores.txt";

void FileManager::PrintFile(ScoreLine record) {
    std::ofstream file;
    file.open (FileManager::file);
    file << record.getName() <<";"<< record.getPoint()<<"\n";
    file.close();
}

ScoreLine* FileManager::sort(){

}

ScoreLine* FileManager::readFile(){
    std::string line;
    std::ifstream myfile (FileManager::file);

    std::list<ScoreLine> fc;
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {

        }
        myfile.close();
    }

    else std::cout << "Unable to open file\n";
    return NULL;
}