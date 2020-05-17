//
// Created by jani on 2020. 04. 28..
//

#ifndef NAGYHAZI_MENUITEM_HPP
#define NAGYHAZI_MENUITEM_HPP

#include <string>
#include "SDL_Fake.h"
#include "memtrace.h"

class MenuItem {
private:
    std::string content;
    SDL_Color col;
    SDL_Rect pos;
public:
    void setCol(const SDL_Color &col) {
        this->col = col;
    }

    MenuItem(const char *c_str = "", SDL_Rect pos = {0, 0, 0, 0},
             SDL_Color color = {.r = 255, .g = 0, .b = 0, .a = 255}) : content(c_str), col(color), pos(pos){}
    const char* getContent() const {
        return content.c_str();
    }

    void Draw(SDL_Renderer* renderer,TTF_Font* font) const {
        SDL_Surface* surface = TTF_RenderUTF8_Blended(font, content.c_str(), col);
        double scale = (double)pos.h / (double)surface->h;
        SDL_Rect d = {.x = pos.x, .y = pos.y};
        d.w = (int)(scale * (double)surface->w);
        d.h = (int)(scale * (double)surface->h);
        d.y += (int)(((double)pos.h - scale*(double)surface->h)/2.0);
        SDL_RenderDrawRect(renderer,&d);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_RenderCopy(renderer,texture,NULL,&pos);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
    }

    SDL_Rect getPos() const {
        return pos;
    }
};


#endif //NAGYHAZI_MENUITEM_HPP
