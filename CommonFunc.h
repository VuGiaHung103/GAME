#ifndef COMMONFUNC_H_
#define COMMONFUNC_H_

#include<iostream>
#include<string>
#include<SDL2/SDL.h>
#include<SDL2/SDL_mixer.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_ttf.h>



static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event* g_event;

//SCREEN
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 640;
const int SCREEN_BPP = 32;

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;


#endif // COMMONFUNC_H_
