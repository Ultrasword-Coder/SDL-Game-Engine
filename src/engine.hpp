#pragma once
#include <iostream>

#include <SDL2/SDL.h>

#if defined _WIN64
#include <SDL2/SDL_image.h>
#elif defined _WIN32
#include <SDL2/SDL_image.h>
#elif defined __APPLE__
#include <SDL2_image/SDL_image.h>
#elif defined __MACH__
#include <SDL2_image/SDL_image.h>
#else
printerror("OS not supported? You using linux? yucky... no offense of course");
#endif

/*
    Hosts core functions
    ----
    Engine initialization
*/

typedef unsigned int uint;
typedef unsigned char uchar;

namespace Engine
{
    const uint ENGINE_SUCCESS = 0;
    const uint ENGINE_FAILED = 1;
    const uint ENGINE_WINDOW_FAILED = 2;
    const uint ENGINE_RENDERER_FAILED = 3;

    uint init_SDL()
    {
        int result;
        result = SDL_Init(SDL_INIT_VIDEO);
        if (result)
        {
            SDL_Log("FILE: `engine.hpp` | Failed to initialize SDL Library!\n");
            return ENGINE_FAILED;
        }
        SDL_Log("FILE: `engine.hpp` | Successfully loaded SDL!\n");
        return ENGINE_SUCCESS;
    }

    uint init_SDL_image()
    {
        int result;
        result = IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
        if (!result)
        {
            SDL_Log("FILE: `engine.hpp` | SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
            return ENGINE_FAILED;
        }
        SDL_Log("FILE: `engine.hpp` | Successfully loaded SDL_image!\n");
        return ENGINE_SUCCESS;
    }

    void clean()
    {
        IMG_Quit();
        SDL_Quit();

        SDL_Log("Closed SDL Image and SDL Library\n");
    }
}

// ---------- engine stuff ----------- //

// color typedef
typedef SDL_Color Color;

void output_color_string(Color *color)
{
    // output color as a string of r, g, b, a
    std::cout << "Color | Red: " << +color->r << " | Green: " << +color->g << " | Blue: " << +color->b << " | Alpha: " << +color->a;
}
