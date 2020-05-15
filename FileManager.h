//
// Created by jani on 2020. 04. 27..
//

#ifndef NAGYHAZI_FILEMANAGER_H
#define NAGYHAZI_FILEMANAGER_H

#include <iostream>
#include "ScoreLine.hpp"
#include "SDL_Fake.h"
#include "Display.h"
#include "memtrace.h"

class FileManager {
    std::vector<ScoreLine> content;
public:
    FileManager();
    void Save(ScoreLine record,const char* FILE = "../assets/scores.txt");
    std::vector<ScoreLine> getTop(std::string FileName = "../assets/scores.txt");
    void listContent(Display& d);
    void Draw(Display& display);

};
struct GreaterScore{
    bool operator()(const ScoreLine& first,const ScoreLine& second) const;
};

#endif //NAGYHAZI_FILEMANAGER_H
