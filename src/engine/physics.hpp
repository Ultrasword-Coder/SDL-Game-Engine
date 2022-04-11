#pragma once
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

    File contains physics objects and other physics things

*/

typedef SDL_Rect Rect;

namespace e_Physics
{
    // --------------- Physics Body Struct ------------- //

    struct PhysicsBody
    {
        double xpos;
        double ypos;
        double xmotion;
        double ymotion;
        Rect body;
    };

    // ------------- methods for physics --------------- //

}