//
// Created by jani on 2020. 04. 27..
//
#include <iostream>
#include <algorithm>
#include "SDL_ttf.h"
#include "FileManager.h"
#include "ScoreLine.hpp"
#include "SDL_Fake.h"
#include "MenuItem.hpp"
#include "memtrace.h"

bool GreaterScore::operator()(const ScoreLine& first,const ScoreLine& second) const {
    return first.getScore() > second.getScore();
}

void FileManager::Save(ScoreLine record,const char* FILE) {
    std::ofstream outputFile;
    outputFile.open(FILE, std::ios_base::app);
    outputFile<<record.ToString()<<std::endl;
    outputFile.close();
}
std::vector<ScoreLine> FileManager::getTop(std::string FileName){
    std::ifstream input;
    input.open(FileName.c_str());
    if(input.bad())std::cerr<<"Error at file opening, mode: reading"<<std::endl;
    std::vector<ScoreLine> tmp;
    std::string line;
    int i = 0;
    while (i < 20 && std::getline(input,line)){
        ScoreLine tempScore(line.c_str());
        tmp.push_back(tempScore);
    }
    std::sort(tmp.begin(),tmp.end(),GreaterScore());
    return tmp;
}
FileManager::FileManager(){
    content = getTop();
}
void FileManager::listContent(Display &d) {
    int verticalOffset = 70;
    SDL_Color color = {0,0,0,0};
    std::cout<<content.size()<<std::endl;
    for (int i = 0; i < content.size(); ++i) {
        SDL_Rect drawingRect = {.x = 30,.y = verticalOffset + i * 20,.w = d.getScreenWidth()-100,.h = 20};
        std::stringstream stream;
        stream << content[i].getScore();
        std::string tmp = content[i].getName() + " " + stream.str();
        SDL_Surface* surface = TTF_RenderUTF8_Blended(d.getFont(),tmp.c_str(),color);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(d.renderer,surface);
        SDL_RenderCopy(d.renderer,texture,NULL,&drawingRect);
        std::cout<<tmp<<std::endl;
    }

}
void FileManager::Draw(Display& display){
    SDL_RenderClear(display.renderer);
    display.drawBG();
    std::vector<MenuItem*> subtitles;
    SDL_Color black = {.r = 0, .g = 0,.b = 0, .a = 255};
    SDL_Rect drawingRect = {.x = 0,.y=10,.w = display.getScreenWidth(),.h = 60};
    SDL_Surface* surface = TTF_RenderUTF8_Blended(display.getFont(),"ScoreBoard",black);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(display.renderer, surface);

    double scaleX = (double)drawingRect.w/(double)surface->w;
    double scaleY = (double)drawingRect.h/(double)surface->h;
    bool alignToX = scaleX < scaleY;
    double scale = alignToX ? scaleX : scaleY;
    SDL_Rect d = {.x = drawingRect.x, .y = drawingRect.y};
    d.w = (int)(scale * (double)surface->w);
    d.h = (int)(scale * (double)surface->h);
    if(alignToX){
        d.y += (int)(((double)drawingRect.h - scale*(double)surface->h)/2.0);
    }else{
        d.x += (int)(((double)drawingRect.w - scale*(double)surface->w)/2.0);
    }
    SDL_RenderCopy(display.renderer, texture, NULL, &d);
    listContent(display);
    SDL_RenderPresent(display.renderer);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);

    SDL_Event ev;
    //Exit to menu
    while(SDL_WaitEvent(&ev))
    {
        if(ev.type == SDL_KEYDOWN)
            if(ev.key.keysym.sym == SDLK_ESCAPE)
            break;
    }
}
