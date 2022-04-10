#pragma once
#include <SDL2/SDL.h>
#include <map>

// is more of a static class
namespace Keyboard
{

    // keyboard stuff
    // https://stackoverflow.com/questions/3578083/what-is-the-best-way-to-use-a-hashmap-in-c
    // finally omg
    std::map<int, bool> keys;

    void key_pressed(int key)
    {
        keys[key] = true;
    }

    void key_release(int key)
    {
        keys[key] = false;
    }

    bool is_key_pressed(int key)
    {
        if (keys.find(key) != keys.end())
        {
            return keys[key];
        }
        else
        {
            keys[key] = false;
            return false;
        }
    }

}