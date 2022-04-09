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
printerror("OS not supported? You using linux? yucky... no offense of course");
#endif

#include <iostream>

#include "utils.hpp"

typedef SDL_Rect Rect;

// -------------------- texture class ------------------ //
class Texture
{
private:
    int w, h;
    const char *file;
    Rect rect;

    SDL_Texture *texture;

public:
    bool initialized = false;

    Texture() : w(0), h(0) {}

    Texture(SDL_Texture *tex, const char *path) : file(path), texture(tex)
    {
        // now we get the information
        set_params(tex, path);
    }

    ~Texture()
    {
    }

    void clean()
    {
        // clean texture
        SDL_DestroyTexture(this->texture);
    }

    // ------------------ methods ------------- //

    int get_width()
    {
        return this->w;
    }

    int get_height()
    {
        return this->h;
    }

    const char *get_file()
    {
        return this->file;
    }

    Rect *get_rect()
    {
        // get image rect
        return &this->rect;
    }

    SDL_Texture *get_texture()
    {
        return this->texture;
    }

    void output_log()
    {
        std::cout << "FileName: " << this->file << "| Width: " << this->w << " | Height: " << this->h << std::endl;
    }

    void set_params(SDL_Texture *texture, const char *path)
    {
        initialized = true;
        // get info
        SDL_QueryTexture(texture, NULL, NULL, &this->w, &this->h);
        this->texture = texture;
        rect.x = 0;
        rect.y = 0;
        rect.w = this->w;
        rect.h = this->h;
        // SDL_Log("%d %d", w, h);
    }

    // TODO - add clipping textures etc etc
    // idk how to tho T-T
};