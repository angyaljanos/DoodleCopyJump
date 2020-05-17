//
// Created by mike on 27/04/2020.
//

#ifndef NHF_SDL_H
#define NHF_SDL_H

#ifndef MEMTRACE
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2_gfxPrimitives.h>
#else
#include <cstdlib>
#define SDL_INIT_EVERYTHING (0)
#define SDL_TEXTEDITINGEVENT_TEXT_SIZE (32)

typedef char SDL_Renderer;
typedef char SDL_Texture;
typedef char SDL_Window;
typedef char TTF_Font;
typedef size_t SDL_TimerID;
typedef unsigned long int Uint32;

typedef enum {
    SDL_SCANCODE_W,
    SDL_SCANCODE_A,
    SDL_SCANCODE_S,
    SDL_SCANCODE_D,
    SDL_SCANCODE_UP,
    SDL_SCANCODE_DOWN,
    SDL_SCANCODE_LEFT,
    SDL_SCANCODE_RIGHT,
} SDL_Scancode;

typedef enum {
    SDLK_DOWN,
    SDLK_RIGHT,
    SDLK_UP,
    SDLK_LEFT,
    SDLK_d,
    SDLK_a,
    SDLK_w,
    SDLK_s,
    SDLK_ESCAPE,
    SDLK_SPACE,
    SDLK_BACKSPACE,
    SDLK_RETURN,
} SDL_Keysym;

typedef enum {
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOW_FULLSCREEN_DESKTOP,
    SDL_RENDERER_ACCELERATED,
    SDL_RENDERER_SOFTWARE,
    SDL_RENDERER_PRESENTVSYNC,
} SDL_Misc;

typedef enum {
    SDL_USEREVENT,
    SDL_KEYDOWN,
    SDL_MOUSEBUTTONDOWN,
    SDL_QUIT,
    SDL_MOUSEMOTION,
    SDL_LASTEVENT,
    SDL_TEXTINPUT,
    SDL_TEXTEDITING,
} SDL_EventType;

typedef enum {
    IMG_INIT_JPG,
    IMG_INIT_PNG,
} IMG_Options;

typedef struct {
    int x;
    int y;
    int w;
    int h;
} SDL_Rect;

typedef struct {
    int r;
    int g;
    int b;
    int a;
} SDL_Color;

typedef struct {
    int w;
    int h;
} SDL_Surface;

typedef struct {
    SDL_EventType type;
    struct {
        struct {
            SDL_Scancode scancode;
            SDL_Keysym sym;
        } keysym;
    } key;
    struct {
        int x;
        int y;
    } button;
    struct {
        int x;
        int y;
    } motion;
    struct {
        const char* text;
    } text;
    struct {
        const char* text;
    } edit;
} SDL_Event;

typedef struct {
    int w;
    int h;
} SDL_DisplayMode;

void SDL_SetRenderDrawColor(SDL_Renderer*, int, int, int, int);
SDL_Window* SDL_CreateWindow(const char*, SDL_Misc, SDL_Misc, int, int, int);
SDL_Renderer* SDL_CreateRenderer(SDL_Window*, int, int);
void SDL_GetCurrentDisplayMode(int, SDL_DisplayMode*);
SDL_TimerID SDL_AddTimer(Uint32, Uint32(*)(Uint32, void*), void*);
int SDL_Init(int);
void SDL_Delay(int);
void SDL_RenderPresent(SDL_Renderer*);
int TTF_Init();
TTF_Font* TTF_OpenFont(const char*, int);
void SDL_RemoveTimer(SDL_TimerID);
void SDL_RenderClear(SDL_Renderer*);
void SDL_DestroyRenderer(SDL_Renderer*);
void TTF_CloseFont(TTF_Font*);
void SDL_FreeSurface(SDL_Surface*);
void SDL_DestroyTexture(SDL_Texture*);
void SDL_DestroyWindow(SDL_Window*);
void SDL_RenderDrawRect(SDL_Renderer*, SDL_Rect*);
void SDL_RenderFillRect(SDL_Renderer*, SDL_Rect*);
SDL_Surface* TTF_RenderUTF8_Blended(TTF_Font*, const char*, SDL_Color);
SDL_Texture* SDL_CreateTextureFromSurface(SDL_Renderer*, SDL_Surface*);
void SDL_RenderCopy(SDL_Renderer*, SDL_Texture*, SDL_Rect*, const SDL_Rect*);
void SDL_RenderCopy(SDL_Renderer*, SDL_Texture*, SDL_Rect*, SDL_Rect*);
int SDL_GetTicks();
int SDL_PollEvent(SDL_Event*);
int SDL_PushEvent(SDL_Event*);
const char* SDL_GetError();
const char* TTF_GetError();
void SDL_Quit();
int IMG_Init(int);
void IMG_Quit();
SDL_Texture* IMG_LoadTexture(SDL_Renderer*, const char*);
void SDL_Log(const char* fmt, ...);
int SDL_WaitEvent(SDL_Event*);
void SDL_StartTextInput();
void SDL_StopTextInput();
void boxRGBA(SDL_Renderer*, int, int, int, int, int, int, int, int);
void rectangleRGBA(SDL_Renderer*, int, int, int, int, int, int, int, int);
void vlineRGBA(SDL_Renderer*, int, int, int, int, int, int, int);


void FakeSDLMakeError(bool);
void FakeSDLRunTimers(Uint32 t);

#endif

#endif //NHF_SDL_H
