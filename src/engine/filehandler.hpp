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

#include <unordered_map>
#include <vector>

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

typedef SDL_Rect Rect;
typedef unsigned int uint;

namespace Graphics
{
    // -------------------- pre definitions ---------------- //
    class Texture;
    class SpriteSheet;

    struct SpriteObject;
    struct SpriteSheetSpriteData;

    // -------------------- texture class ------------------ //
    class Texture
    {
    private:
        const char *file;
        Rect rect;

        SDL_Texture *texture;

    public:
        bool initialized;

        Texture() : initialized(false) {}

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
            return this->rect.w;
        }

        int get_height()
        {
            return this->rect.h;
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
            std::cout << "FileName: " << this->file << "| Width: " << this->rect.w << " | Height: " << this->rect.h << std::endl;
        }

        void set_params(SDL_Texture *texture, const char *path)
        {
            initialized = true;
            // get info
            SDL_QueryTexture(texture, NULL, NULL, &this->rect.w, &this->rect.h);
            this->texture = texture;
            rect.x = 0;
            rect.y = 0;
            // SDL_Log("%d %d", w, h);
        }

        // TODO - add clipping textures etc etc
        // idk how to tho T-T
    };

    // -------------------- sprite sheet stuff ------------- //

    // ----- sprite object --- //
    struct SpriteObject
    {
        uint id;
        Rect area;
    };

    void output_spriteobject(SpriteObject *obj)
    {
        SDL_Log("FILE: `filehandler.hpp` | SpriteObject<id=%d, x=%d, y=%d, w=%d, h=%d>",
                obj->id, obj->area.x, obj->area.y, obj->area.w, obj->area.h);
    }

    // sprite sheet sprite object ---- //

    struct SpriteSheetSpriteData
    {
        uint sprite_count;
        uint sprite_width;
        uint sprite_height;
        uint x_padding;
        uint y_padding;
    };

    class SpriteSheet
    {
    private:
        Texture *sheet;
        std::vector<SpriteObject> sprites;

        uint sprite_count;
        uint sprite_width, sprite_height;
        uint x_padding, y_padding;
        uint initialized;

    public:
        SpriteSheet(Texture *tex, uint count, uint width, uint height, uint padx = 0, uint pady = 0) : sheet(tex), sprite_count(count), sprite_width(width),
                                                                                                       sprite_height(height), x_padding(padx), y_padding(pady), initialized(0) {}

        ~SpriteSheet() {}

        void create()
        {
            // create the sprite sheet and everything in its glory
            int left = this->x_padding, top = this->y_padding;
            // uint x_lim = (this->sheet->get_width() - this->x_padding) / (this->x_padding + this->sprite_width);
            int img_width = (int)this->sheet->get_width(), img_height = (int)this->sheet->get_height();
            int s_width = (int)this->sprite_width, s_height = (int)this->sprite_height;

            // looping time!
            uint id = 0;
            for (int i = 0; i < this->sprite_count; i++)
            {
                // capture image
                SpriteObject obj = {id, {left, top, s_width, s_height}};
                // output for debug
                // DEBUG - output_spriteobject(&obj);
                // add to vector
                this->sprites.push_back(obj);
                // calculate next position
                left += sprite_width + this->x_padding;
                // only increment y when x is out of bounds
                if (left >= img_width)
                {
                    left = this->x_padding;
                    top += this->sprite_height + this->y_padding;
                }
                id++;
            }

            this->initialized = 1;
        }

        // --------------- methods --------------- //
        Texture *get_texture()
        {
            // return the texture
            return this->sheet;
        }

        uint get_width()
        {
            return this->sprite_width;
        }

        uint get_height()
        {
            return this->sprite_height;
        }

        uint get_xpad()
        {
            return this->x_padding;
        }

        uint get_ypad()
        {
            return this->y_padding;
        }

        uint get_count()
        {
            return this->sprite_count;
        }

        SpriteObject *sprite_at(int pos)
        {
            return &this->sprites.at(pos);
        }

        SpriteSheetSpriteData get_specs()
        {
            return {this->sprite_count, this->sprite_width, this->sprite_height, this->x_padding, this->y_padding};
        }

        // ---------------- etc ------------------ //
    };

}

namespace ImageHandler
{
    // --------- image cache ------------ //
    std::unordered_map<const char *, Graphics::Texture> texture_cache;

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
    Graphics::Texture *load_image(SDL_Renderer *renderer, const char *path)
    {
        // check if already loaded
        if (texture_cache[path].initialized)
        {
            // then skip over and return
            return &texture_cache[path];
        }
        // load an image from given path and renderer
        Graphics::Texture tex;
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
