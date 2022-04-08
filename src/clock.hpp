#pragma once
#include <iostream>

#include "SDL2/SDL_timer.h"


typedef unsigned int uint;


namespace Clock{

    const uint SECOND = 1000;

    uint engine_start_time;
    uint start_time;
    uint end_time;
    uint delta_time;
    uint wait_time;         // unnecassary
    double delta;

    uint fps;
    uint frame_time;


    void start(uint fps = 0){
        Clock::fps = fps;
        frame_time = fps > 0 ? Clock::SECOND / Clock::fps : 0;
        engine_start_time = start_time = SDL_GetTicks()-frame_time;
        std::cout << "Engine Started: " << engine_start_time << "ms" << " | Frame Time: " << (frame_time>0 ? frame_time : 1000/60) << "ms" << std::endl;
    }

    void update(){
        // get end time
        end_time = SDL_GetTicks();
        delta_time = end_time - start_time;
        // update float delta time
        if(delta_time>0) delta = 1/(double)delta_time;
        start_time = end_time;
    }

    void update_no_vsync(){
        // for non vsync programs
        end_time = SDL_GetTicks();
        delta_time = end_time - start_time;
        if(frame_time < delta_time) wait_time = 0;
        else wait_time = frame_time - delta_time;
        SDL_Delay(wait_time);
        start_time = end_time + wait_time;
    }

}
