#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include <unordered_map>
#include <string>

#include "physics.hpp"
#include "filehandler.hpp"
#include "window.hpp"
#include "draw.hpp"

/*

    World container object
    - contains chunks, tilesheets

    World Editor included? nop

*/

typedef unsigned int uint;
typedef unsigned char uchar;
typedef SDL_Rect Rect;

namespace World
{
    const int CHUNK_WIDTH = 8;
    const int CHUNK_HEIGHT = 8;

    const int TILE_WIDTH = 32;
    const int TILE_HEIGHT = 32;

    const int CHUNK_WIDTH_PIX = TILE_WIDTH * CHUNK_WIDTH;
    const int CHUNK_HEIGHT_PIX = TILE_HEIGHT * CHUNK_HEIGHT;

    const int TILE_DATA_SIZE = 1;
    const int TILE_COLLIDEABLE = 0;

    // -------- pre def --------- //
    class World;
    struct Chunk;
    struct Tile;

    // -------- tile ------------ //

    struct Tile : Rect
    {
        // holds positional data
        std::string tex;
        bool data[TILE_DATA_SIZE];
    };

    // -------- chunk ----------- //

    struct Chunk
    {
        long chunk_id;
        int posx;
        int posy;
        int world_pos_x;
        int world_pos_y;
        bool initialized; // bool default init value is 0 -> false

        // hold the tile grid
        Tile grid[CHUNK_WIDTH][CHUNK_HEIGHT];
    };

    static long get_chunk_id(int x, int y)
    {
        return x + (y << 16);
    }

    static long get_chunk_id(Chunk *chunk)
    {
        return chunk->posx + (chunk->posy << 16);
    }

    static void set_tile_at(Chunk *chunk, Tile *tile)
    { // set a tile in a certain chunk
        Tile *block = &chunk->grid[tile->y][tile->x];
        block->x = tile->x * TILE_WIDTH + chunk->world_pos_x;
        block->y = tile->y * TILE_HEIGHT + chunk->world_pos_y;
        block->w = TILE_WIDTH;
        block->h = TILE_HEIGHT;
        block->tex = tile->tex;
        for (int i = 0; i < TILE_DATA_SIZE; i++)
            block->data[i] = tile->data[i];
    }

    // -------- World ----------- //

    class World
    {
        // world object
    private:
        // unordered map of chunks
        std::unordered_map<long, Chunk> chunks;

        int render_distance;

    public:
        World() : render_distance(2){};
        ~World()
        {
            this->chunks.clear();
        }

        // --------- methods -------------- //

        Chunk *make_template_chunk(int cx, int cy)
        {
            // create the chunk and cache it as well
            Chunk result;
            result.posx = cx;
            result.posy = cy;
            result.chunk_id = get_chunk_id(cx, cy);
            result.world_pos_x = CHUNK_WIDTH_PIX * cx;
            result.world_pos_y = CHUNK_HEIGHT_PIX * cy;
            result.initialized = true;
            // cache chunk
            chunks[result.chunk_id] = result;
            return &chunks[result.chunk_id];
        }

        Chunk *get_chunk(int cx, int cy)
        {
            // get a chunk
            if (!chunks[get_chunk_id(cx, cy)].initialized)
                // if not exist return nothing
                return nullptr;
            return &chunks[get_chunk_id(cx, cy)];
        }

        // TODO - render chunks
        void render_chunks(int relx, int rely, int offx = 0, int offy = 0)
        {
            // loop through all valid chunks in render distance and render them
            Chunk *chunk;
            Tile *tile;
            for (int x = relx - render_distance; x <= render_distance + relx; x++)
                for (int y = rely - render_distance; y <= render_distance + rely; y++)
                {
                    chunk = get_chunk(x, y);
                    if (!chunk)
                        continue;
                    // render chunk
                    for (int tx = 0; tx < CHUNK_WIDTH; tx++)
                        for (int ty = 0; ty < CHUNK_HEIGHT; ty++)
                        {
                            // render the block
                            tile = &chunk->grid[ty][tx];
                            if (tile->tex.length())
                            {
                                // SDL_Log("%d, %d", tile->w, tile->h);
                                // if tex exists, render
                                Draw::blit(&ImageHandler::texture_cache[tile->tex], tile);
                            }
                        }
                }
        }

        Tile create_tile(int gridx, int gridy, std::string image, bool collideable = false)
        {
            Tile result;
            result.x = gridx;
            result.y = gridy;
            result.w = TILE_WIDTH;
            result.h = TILE_HEIGHT;
            result.tex = image;
            result.data[TILE_COLLIDEABLE] = collideable;
            ImageHandler::load_image(Window::instance_renderer, image);
            return result;
        }

        // ------- setters and getters ---------- //
        int get_render_distance()
        {
            return this->render_distance;
        }

        void set_render_distance(int distance)
        {
            this->render_distance = distance;
        }
    };
}
