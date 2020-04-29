#include <iostream>
#include "Playground.h"
#include "Display.h"
#include "FileManager.h"

#include "SDL_Fake.h"

//Az asset mappa a mérete miatt nem feltölthető de elérhető az alábbi linken
// https://github.com/angyaljanos/DoodleCopyJump
int main() {
    Display display;
    //FileManager fm;
    //Playground game;
    SDL_Event event;
    SDL_PollEvent(&event);

    while ( SDL_WaitEvent(&event) && event.type != SDL_QUIT) {
        Vector2D mousePosition((double)event.motion.x,(double)event.motion.y);
        display.drawMenu(mousePosition);
        SDL_RenderPresent(display.renderer);
        switch(display.chooseMenu(mousePosition)){
            case 0:
                std::cout<<"elso"<<std::endl;
                break;
            case 1:
                std::cout<<"masodik"<<std::endl;
                break;
            case 2:
                std::cout<<"harmadik"<<std::endl;
                break;
            default:break;
        }

    }
    return 0;
}
