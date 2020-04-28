//
// Created by jani on 2020. 04. 27..
//
#include <iostream>
#include <fstream>
#include <list>
#include "FileManager.h"
#include "ScoreLine.hpp"
#include "SDL_Fake.h"

std::string FileManager::file = "Scores.txt";

void FileManager::PrintFile(ScoreLine record) {
    std::ofstream File;
    File.open (FileManager::file);
    File << record.getName() <<";"<< record.getPoint()<<"\n";
    File.close();
}

ScoreLine* FileManager::sort(){
    return NULL;
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
