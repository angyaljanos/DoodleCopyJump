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

///@brief Fájlkezelést végző osztály deffiníciója
class FileManager {
    ///@brief A rendezés fájlban tárolt adatok első 20 elemét tárolja
    std::vector<ScoreLine> content;
    void alignTextInRect(SDL_Renderer* renderer, TTF_Font* font, std::string string, SDL_Rect* dest, SDL_Color color);
public:
    FileManager();
    void SaveRecord(ScoreLine record, const char* FILE = "../assets/scores.txt");
    std::vector<ScoreLine> LoadContent(std::string FileName = "../assets/scores.txt");
    void listContent(Display& d);
    void Draw(Display& display);

};
///@brief ScoreLine összehasonlítást végző predikátum
struct GreaterScore{
    bool operator()(const ScoreLine& first,const ScoreLine& second) const;
};

#endif //NAGYHAZI_FILEMANAGER_H
