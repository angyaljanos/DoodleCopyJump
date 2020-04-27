//
// Created by jani on 2020. 04. 27..
//

#ifndef NAGYHAZI_FILEMANAGER_H
#define NAGYHAZI_FILEMANAGER_H

#include <iostream>
#include "ScoreLine.hpp"

class FileManager {
    static std::string file;
    ScoreLine* content;

    ScoreLine* readFile();
    ScoreLine* sort();
public:
    void PrintFile(ScoreLine record);
    ScoreLine* getTop(unsigned int);
};


#endif //NAGYHAZI_FILEMANAGER_H