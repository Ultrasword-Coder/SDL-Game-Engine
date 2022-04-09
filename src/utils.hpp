#pragma once
#include "SDL2/SDL.h"

#include <iostream>

namespace Utils
{

    // -------------- error handling ---------------- //

    char buffer[500];

    void handle_error()
    {
        SDL_GetErrorMsg(buffer, 500);
        SDL_Log(buffer);
    }

}
