#pragma once
#include "SDL2/SDL.h"

#include <iostream>
#include <cassert>

#include "engine.hpp"
#include "texture.hpp"
#include "utils.hpp"

/*
    There will only be one window instance at a time
*/

typedef unsigned int uint;

namespace Window
{

    struct Window_Data
    {
        const char *title;
        uint width;
        uint height;
        uint flags;
        uint bit_depth;
        bool vsync;

        uint xpos;
        uint ypos;
    };

    SDL_Window *instance;
    SDL_Renderer *instance_renderer;
    Window_Data instance_data;

    bool running = false;

    void create_instance(const char *title, uint width, uint height, uint flags = 0, uint bit_depth = 32, bool vsync = true, uint xpos = SDL_WINDOWPOS_CENTERED, uint ypos = SDL_WINDOWPOS_CENTERED)
    {
        instance_data.title = title;
        instance_data.width = width;
        instance_data.height = height;
        instance_data.flags = flags;
        instance_data.bit_depth = bit_depth;
        instance_data.vsync = vsync;

        // change settings
        if (instance)
        {
            // change window settings
            std::cout << "FILE: `window.hpp` | Implement this plz" << std::endl;
        }
        else
        {
            // create new window
            instance = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
            if (!instance)
            {
                // errors!
                std::cout << "FILE: `window.hpp` | Failed to create new window with title `" << title << "`!" << std::endl;
                assert(false);
            }

            // create renderer
            instance_renderer = SDL_CreateRenderer(instance, -1, SDL_RENDERER_PRESENTVSYNC);
            if (!instance_renderer)
            {
                // errors!
                std::cout << "FILE: `window.hpp` | Failed to create window renderer!" << std::endl;
                assert(false);
            }
        }
    }

    void clean()
    {
        if (instance_renderer)
            SDL_DestroyRenderer(instance_renderer);
        if (instance)
            SDL_DestroyWindow(instance);
    }

    void fill(Color *color)
    {
        // fill the screen with a color
        SDL_SetRenderDrawColor(instance_renderer, color->r, color->g, color->b, color->a);
        SDL_RenderFillRect(instance_renderer, NULL);
    }

    void blit(SDL_Texture *tex, SDL_Rect *src, SDL_Rect *dst)
    {
        //  render the texture of src rect to dest rect
        SDL_RenderCopy(instance_renderer, tex, src, dst);
    }

    void blit(Texture *tex, SDL_Rect *dst)
    {
        // render the tex given the original src and the dest rect
        SDL_RenderCopy(instance_renderer, tex->get_texture(), tex->get_rect(), dst);
    }

}