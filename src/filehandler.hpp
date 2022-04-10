#pragma once
#include "SDL2/SDL.h"

#if defined _WIN64
#include "SDL2/SDL_image.h"
#elif defined _WIN32
#include "SDL2/SDL_image.h"
#elif defined __APPLE__
#include "SDL2/SDL_Image.h"
#elif defined __MACH__
#include "SDL2/SDL_Image.h"
#else
printerror("OS not supported? You using linux?");
#endif

#include <unordered_map>

#include "window.hpp"
#include "utils.hpp"

/*
    Image Handler system
    - png
    - jpg
    - thats it

    Audio Handler system
    - to be implemented ;-;
    - i hate audio
    - im assuming just .wav files but i wanna try .mp3 files as well
*/

namespace ImageHandler
{
    // --------- image cache ------------ //
    std::unordered_map<const char *, Texture> texture_cache;

    // memory cleaning
    void clean()
    {
        for (auto &obj : texture_cache)
        {
            obj.second.clean();
            SDL_Log("CLEAN: Cleaned %s from RAM!", obj.first);
        }
    }

    // handles opening images - png and jpg
    Texture *load_image(SDL_Renderer *renderer, const char *path)
    {
        // check if already loaded
        if (texture_cache[path].initialized)
        {
            // then skip over and return
            return &texture_cache[path];
        }
        // load an image from given path and renderer
        Texture tex;
        SDL_Texture *loaded = NULL;
        // get image
        loaded = IMG_LoadTexture(renderer, path);
        // error checking
        if (!loaded)
        {
            SDL_Log("ERROR: `filehandler.hpp` | Failed to load file at `%s`\n", path);
            Window::running = false;
            Utils::handle_error();
            return NULL;
        }

        // image was loaded and now set parameters
        tex.set_params(loaded, path);
        ImageHandler::texture_cache[path] = tex;
        return &ImageHandler::texture_cache[path];
    }
}
