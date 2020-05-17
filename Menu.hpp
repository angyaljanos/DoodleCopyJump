//
// Created by jani on 2020. 05. 08..
//

#ifndef NAGYHAZI_MENU_HPP
#define NAGYHAZI_MENU_HPP

#include <string>
#include <vector>
#include "Vector2D.h"
#include "MenuItem.hpp"
#include "Display.h"
#include "Playground.h"

#include "memtrace.h"
///@brief A menüt leíró osztály deffiníció
class Menu {
private:
    std::vector<MenuItem*> items;
public:
    Menu(const std::vector<std::string>& subtitle = {"Let's Play","Scoreboard","Quit"}){
        items.resize(subtitle.size());
        Vector2D OFFSET(20,20),buttonDimensions(160,40);
        int gap = 65;
        for (int i = 0; i < subtitle.size(); ++i) {
            SDL_Rect destRect = {
                    .x = (int)OFFSET.x,
                    .y = (int)OFFSET.y + (int)i * gap,
                    .w = (int)buttonDimensions.x + 50,
                    .h = (int)buttonDimensions.y
            };
            items[i] = new MenuItem(subtitle[i].c_str(), destRect);
        }
    }
    /**@brief A Menü rajzolásáért felelős függvény
     *
     * @param display - A kijelző, amelyre rajzolni szeretnénk
     * @param Mouse - Az egér helye az ablakon belül(x és y koordináták)
     * @param ev - A felhasználó által a programban adott esemény
     */
    void DrawMenu(Display& display, Vector2D& Mouse,SDL_Event& ev){
        display.drawBG();
        SDL_Color hoverColor = {.r = 168 ,.g = 153, .b = 50,.a = 200};
        SDL_Color normalColor = {.r = 50, .g = 98, .b = 168, .a = 195};

            for (size_t i = 0; i < items.size(); ++i) {
                items[i]->Draw(display.renderer, display.getFont());
                if(ev.type == SDL_MOUSEMOTION) {
                    if (Playground::CollisionCheck(Vector2D(items[i]->getPos().x, items[i]->getPos().y),
                                               Vector2D(items[i]->getPos().w, items[i]->getPos().h), Mouse,
                                               Vector2D(5, 5))) {
                        items[i]->setCol(hoverColor);
                    } else items[i]->setCol(normalColor);
            }
        }
    }
    ///@brief Menüben való választást végző függvény, ha a kattintás nem egy listaelemen történt -1 ad vissza
    int chooseMenu(Vector2D MousePosition,SDL_Event& event) {
        int choosen = -1;

        if(event.type == SDL_MOUSEBUTTONDOWN)
            for (size_t i = 0; i < items.size(); i++) {
                {
                    if(Playground::CollisionCheck(Vector2D(items[i]->getPos().x,items[i]->getPos().y),
                                                  Vector2D(items[i]->getPos().w,items[i]->getPos().y),
                                                  MousePosition,
                                                  Vector2D(1,1)))
                    {
                        choosen = i;
                        std::cout<<choosen<<std::endl;
                    }
                }
            }
        return choosen;
    }
    ~Menu(){
        for (std::vector<MenuItem*>::iterator i = items.begin(); i != items.end();++i) {
            delete *i;
        }
    }
};


#endif //NAGYHAZI_MENU_HPP
