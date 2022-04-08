#pragma once
#include <iostream>

#include "SDL2/SDL.h"
#include "SDL2_image/SDL_Image.h"


/*
    Hosts core functions
    ----
    Engine initialization
*/

typedef unsigned int uint;
typedef unsigned char uchar;

namespace Engine{
    const uint ENGINE_SUCCESS = 0;
    const uint ENGINE_FAILED = 1;
    const uint ENGINE_WINDOW_FAILED = 2;
    const uint ENGINE_RENDERER_FAILED = 3;


    uint init_SDL(){
        int result;
        result = SDL_Init(SDL_INIT_VIDEO);
        if(result){
            std::cout << "Failed to initialize SDL Library!" << std::endl;
            return ENGINE_FAILED;
        }
        return ENGINE_SUCCESS;
    }

    uint init_SDL_image(){
        int result;
        result = IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
        if(!result){
            std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
            return ENGINE_FAILED;
        }
        return ENGINE_SUCCESS;
    }

    void clean(){
        IMG_Quit();
        SDL_Quit();
    }
}

// ---------- engine stuff ----------- //

// color typedef
typedef SDL_Color Color;

void output_color_string(Color* color){
    // output color as a string of r, g, b, a
    std::cout << "Color | Red: " << +color->r << " | Green: " << +color->g << " | Blue: " << +color->b << " | Alpha: " << +color->a;
}




