#ifdef MEMTRACE
#include "SDL_Fake.h"
#include <cstdio>
#include <vector>
#include "memtrace.h"

/*
 * Hamis SDL-t (csúnyán) megvalósító függvények.
 * Csak és kizárólag a tesztesetek SDL nélküli futtatásához.
 * */

static bool makeError = false;
static bool didSDLInit = false;
static bool didTTFInit = false;
typedef Uint32(*timerF)(Uint32, void*);
static timerF timers[100] = {NULL};
static void* ptrs[100] = {NULL};
static size_t timerSize = 0;

void SDL_SetRenderDrawColor(SDL_Renderer*, int, int, int, int){}
SDL_Window* SDL_CreateWindow(const char*, SDL_Misc, SDL_Misc, int, int, int){
    if (makeError || !didSDLInit)
        return NULL;
    return new SDL_Window;
}
SDL_Renderer* SDL_CreateRenderer(SDL_Window*, int, int){
    if (makeError || !didSDLInit)
        return NULL;
    return new SDL_Renderer;
}
void SDL_GetCurrentDisplayMode(int, SDL_DisplayMode* dm){
    dm->w = 100;
    dm->h = 200;
}
SDL_TimerID SDL_AddTimer(Uint32, timerF t, void* p){
    timers[timerSize] = t;
    ptrs[timerSize++] = p;
    return timerSize-1;
}
int SDL_Init(int){
    didSDLInit = true;
    return 0;
}
void SDL_Delay(int){}
void SDL_RenderPresent(SDL_Renderer*){}
int TTF_Init(){
    didTTFInit = true;
    return 0;
}
TTF_Font* TTF_OpenFont(const char*, int){
    if (makeError || !didTTFInit)
        return NULL;
    return new TTF_Font;
}
void SDL_RemoveTimer(SDL_TimerID i){
    timers[i] = NULL;
    ptrs[i] = NULL;
}
void SDL_RenderClear(SDL_Renderer*){}
void SDL_DestroyRenderer(SDL_Renderer* r){
    delete r;
}
void TTF_CloseFont(TTF_Font* f){
    delete f;
}
void SDL_FreeSurface(SDL_Surface* s){
    delete s;
}
void SDL_DestroyTexture(SDL_Texture* t){
    delete t;
}
void SDL_DestroyWindow(SDL_Window* w){
    delete w;
}
void SDL_RenderDrawRect(SDL_Renderer*, SDL_Rect*){}
void SDL_RenderFillRect(SDL_Renderer*, SDL_Rect*){}
SDL_Surface* TTF_RenderUTF8_Blended(TTF_Font*, const char*, SDL_Color){
    if (makeError || !didSDLInit || !didTTFInit)
        return NULL;
    return new SDL_Surface;
}
SDL_Texture* SDL_CreateTextureFromSurface(SDL_Renderer*, SDL_Surface*){
    if (makeError || !didSDLInit)
        return NULL;
    return new SDL_Texture;
}
SDL_Texture* IMG_LoadTexture(SDL_Renderer*, const char*){
    if (makeError)
        return NULL;
    return new SDL_Texture;
}
void SDL_RenderCopy(SDL_Renderer*, SDL_Texture*, SDL_Rect*, const SDL_Rect*){}
void SDL_RenderCopy(SDL_Renderer*, SDL_Texture*, SDL_Rect*, SDL_Rect*){}
int SDL_GetTicks(){
    return 0;
}
int SDL_PollEvent(SDL_Event* ev){
    ev->type = SDL_LASTEVENT;
    return 0;
}
const char* SDL_GetError(){
    return "CPorta SDL test error";
}
const char* TTF_GetError(){
    return "CPorta SDL test error";
}
void SDL_Quit(){}

void SDL_Log(const char* fmt, ...){}
int SDL_WaitEvent(SDL_Event*){
    return 0;
}
int SDL_PushEvent(SDL_Event*){
    return 0;
}
int IMG_Init(int){
    return 1;
}

void SDL_StartTextInput(){}
void SDL_StopTextInput(){}
void boxRGBA(SDL_Renderer*, int, int, int, int, int, int, int, int){}
void rectangleRGBA(SDL_Renderer*, int, int, int, int, int, int, int, int){}
void vlineRGBA(SDL_Renderer*, int, int, int, int, int, int, int){}

void IMG_Quit() {}

void FakeSDLMakeError(bool make) {
    makeError = make;
}

void FakeSDLRunTimers(Uint32 t) {
    for (size_t i = 0; i < timerSize; ++i) {
        if (timers[i] != NULL)
            timers[i](t, ptrs[i]);
    }
}

#endif