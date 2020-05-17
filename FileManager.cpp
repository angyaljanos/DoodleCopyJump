//
// Created by jani on 2020. 04. 27..
//
#include <iostream>
#include <algorithm>
#include <fstream>
#include "SDL_ttf.h"
#include "FileManager.h"
#include "ScoreLine.hpp"
#include "SDL_Fake.h"
#include "MenuItem.hpp"
#include "memtrace.h"


bool GreaterScore::operator()(const ScoreLine& first,const ScoreLine& second) const {
    return first.getScore() > second.getScore();
}
///@brief Fájlba-író függvény
void FileManager::SaveRecord(ScoreLine record, const char* FILE) {
    std::ofstream outputFile;
    outputFile.open(FILE, std::ios_base::app);
    outputFile<<record.ToString()<<std::endl;
    outputFile.close();
}
///@brief fájlból olvasó függvény
std::vector<ScoreLine> FileManager::LoadContent(std::string FileName){
    std::ifstream input;
    input.open(FileName.c_str());
    if(input.bad())std::cerr<<"Error at file opening, mode: reading"<<std::endl;
    std::vector<ScoreLine> tmp;
    std::string line;
    while (std::getline(input,line)){
        ScoreLine tempScore(line.c_str());
        tmp.push_back(tempScore);
    }
    std::sort(tmp.begin(),tmp.end(),GreaterScore());
    return tmp;
}
///@brief Paraméter nélküli konstruktor, alapértelmezetten feltölti a taralmat tároló tömböt
FileManager::FileManager(){
    content = LoadContent();
}


///@brief A rajzolást végző függvény, a céltéglalap közepére igazítja a szöveget
void FileManager::alignTextInRect(SDL_Renderer* renderer, TTF_Font* font, std::string string, SDL_Rect* dest, SDL_Color color){
    //Source: https://gitlab.com/MikeTTh/bme-2.-semester/-/blob/master/prog/nhf/TextBox.cpp line 10
    SDL_Surface* surface = TTF_RenderUTF8_Blended(font, string.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    double scaleX = (double)dest->w/(double)surface->w;
    double scaleY = (double)dest->h/(double)surface->h;
    bool alignToX = scaleX < scaleY;
    double scale = alignToX ? scaleX : scaleY;
    SDL_Rect d = {.x = dest->x, .y = dest->y};
    d.w = (int)(scale * (double)surface->w);
    d.h = (int)(scale * (double)surface->h);

    if(alignToX){
    d.y += (int)(((double)dest->h - scale*(double)surface->h)/2.0);
    }else{
    d.x += (int)(((double)dest->w - scale*(double)surface->w)/2.0);
    }

    SDL_RenderCopy(renderer, texture, NULL, &d);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}
///@brief content tömb rajzolásáért felelős függvény
void FileManager::listContent(Display &d) {
    int verticalOffset = 70;
    SDL_Color color = {0,0,0,255};
    std::sort(content.begin(),content.end(),GreaterScore());
    for (int i = 0; i < content.size() && i < 20; ++i) {
        SDL_Rect drawingRect = {.x = 30,.y = verticalOffset + i * 20,.w = d.getScreenWidth()-60,.h = 40};
        std::stringstream stream;
        stream << content[i].getName() << " " << std::to_string(content[i].getScore());
        alignTextInRect(d.renderer, d.getFont(), stream.str(), &drawingRect, color);

    }
}
///A dícsőség rajzolását vezérlő  függvény
void FileManager::Draw(Display& display){
    SDL_RenderClear(display.renderer);
    display.drawBG();
    std::vector<MenuItem*> subtitles;
    SDL_Color black = {.r = 0, .g = 0,.b = 0, .a = 255};
    SDL_Rect drawingRect = {.x = 0,.y=10,.w = display.getScreenWidth(),.h = 60};

    alignTextInRect(display.renderer,display.getFont(),"ScoreBoard",&drawingRect,black);
    listContent(display);
    SDL_RenderPresent(display.renderer);

    SDL_Event ev;
    //Exit to menu
    while(SDL_WaitEvent(&ev))
    {
        if(ev.type == SDL_KEYDOWN)
            if(ev.key.keysym.sym == SDLK_ESCAPE)
            break;
    }
}
