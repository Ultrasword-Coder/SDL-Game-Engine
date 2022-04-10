#pragma once
#include <SDL2/SDL.h>

#include "engine.hpp"
#include "window.hpp"
#include "filehandler.hpp"

typedef SDL_Rect Rect;

namespace Draw
{

    // ------- Window ------------- //

    void fill(Color *color)
    {
        // fill the screen with a color
        SDL_SetRenderDrawColor(Window::instance_renderer, color->r, color->g, color->b, color->a);
        SDL_RenderFillRect(Window::instance_renderer, NULL);
    }

    void blit(SDL_Texture *tex, SDL_Rect *src, SDL_Rect *dst)
    {
        //  render the texture of src rect to dest rect
        SDL_RenderCopy(Window::instance_renderer, tex, src, dst);
    }

    void blit(Graphics::Texture *tex, SDL_Rect *dst)
    {
        // render the tex given the original src and the dest rect
        SDL_RenderCopy(Window::instance_renderer, tex->get_texture(), tex->get_rect(), dst);
    }

    // ------ SpriteSheet --------- //
    void render_sprite_object(Graphics::SpriteSheet *sprite_sheet, SDL_Rect *obj, Rect *rect)
    {
        // draw the specific thing onto other thing :D
        SDL_RenderCopy(Window::instance_renderer, sprite_sheet->get_texture()->get_texture(), obj, rect);
    }

}
