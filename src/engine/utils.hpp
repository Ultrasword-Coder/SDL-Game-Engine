#pragma once
#include <SDL2/SDL.h>

#include <iostream>

namespace Utils
{

    // -------------- error handling ---------------- //

    char buffer[500];

    void handle_error()
    {
        SDL_GetErrorMsg(Utils::buffer, 500);
        SDL_Log("%s", Utils::buffer);
    }

}
