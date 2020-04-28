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
        display.drawMenu(Vector2D((double)event.motion.x,(double)event.motion.y));
        SDL_RenderPresent(display.renderer);

    }


    return 0;
}
