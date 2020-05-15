#include <iostream>
#include "Playground.h"
#include "Display.h"
#include "FileManager.h"
#include "Menu.hpp"

#include "SDL_Fake.h"

#include "memtrace.h"
Uint32 timer(Uint32 ms,void* param){
    SDL_Event ev;
    ev.type = SDL_USEREVENT;
    SDL_PushEvent(&ev);
    return ms;
}

//Az asset mappa a mérete miatt nem feltölthető de elérhető az alábbi linken
// https://github.com/angyaljanos/DoodleCopyJump
int main() {
    try {
        Display display;

        FileManager fm;
        Playground game(display);
        Menu menu;
        SDL_Event event;

        SDL_TimerID id = SDL_AddTimer(1000/60,timer,NULL);

        while (SDL_WaitEvent(&event) && event.type != SDL_QUIT) {
            Vector2D mousePosition((double) event.motion.x, (double) event.motion.y);
                menu.DrawMenu(display, mousePosition,event);
                SDL_RenderPresent(display.renderer);
            int p = menu.chooseMenu(mousePosition, event);
            switch (p) {
                case 0:
                    std::cout << "elso" << std::endl;
                    game.Game(display);
                    return 0;

                case 1:
                    std::cout << "masodik" << std::endl;
                    fm.Draw(display);
                    break;
                case 2:
                    SDL_RemoveTimer(id);
                    return 0;

                default:
                    break;
            }

        }
        SDL_RemoveTimer(id);
    }
    catch (std::logic_error& exp) {
        std::cout<<exp.what();
        exit(1);
    }
    return 0;
}
