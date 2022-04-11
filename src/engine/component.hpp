#pragma once

#include <vector>

typedef unsigned int uint;
typedef unsigned char uchar;

// -------------- pre defs ---------------- //
struct Component;
struct ComponentHandler;

// ----------- global component handler --- //

// create a buffer of size
const uint LARGEST = 0xFFFFFFFF;

Component global_cache[LARGEST];

// ------------ components ---------------- //

struct Component
{
    uint id;
    void update(double dt) {}
};

struct ComponentHandler
{
    std::vector<uint> component_ids;

    void update_components(double dt)
    {
        for (int i = 0; i < component_ids.size(); i++)
            global_cache[component_ids.at(i)].update(dt);
    }
};
