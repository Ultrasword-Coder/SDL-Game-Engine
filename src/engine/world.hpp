#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include <unordered_map>

#include "physics.hpp"
#include "filehandler.hpp"


/*

    World container object
    - contains chunks, tilesheets

    World Editor included? nop

*/

typedef unsigned int uint;
typedef unsigned char uchar;

namespace World{
    const int CHUNK_WIDTH = 8;
    const int CHUNK_HEIGHT = 8;

    const int TILE_WIDTH = 32;
    const int TILE_HEIGHT = 32;
    
    const int TILE_COLLIDEABLE = 0;

    // -------- pre def --------- //
    class World;
    struct Chunk;
    struct Tile;

    // -------- tile ------------ //

    struct Tile{
        // holds positional data
        int x;
        int y;
        int tex_id;
        bool[] data = {false};
    };

    // -------- chunk ----------- //

    struct Chunk{
        long chunk_id;
        int x;
        int y;

        // hold the tile grid
        World::Tile grid[CHUNK_WIDTH][CHUNK_HEIGHT];

        static create_tile_at(int gridx, int gridy, )
    };

    // -------- World ----------- //

    class World
    {
        // world object
    private:
        // unordered map of chunks
        std::unordered_map<long, World::Chunk> chunks;
        std::unordered_map<const char*, Graphics::Texture*> textures;
    public:
        World();
        ~World();

        // --------- methods -------------- //

        Chunk* make_template_chunk(int cx, int cy, )
    };
}


