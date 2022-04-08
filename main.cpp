#include <iostream>


#include "SDL2/SDL.h"
#include "SDL2_image/SDL_Image.h"
#include "src/engine.hpp"
#include "src/window.hpp"
#include "src/clock.hpp"


unsigned int WIDTH = 800, HEIGHT = 600;
const char* TITLE = "osu! but scam";
bool running = false;


int main(int argc, char* argv[])
{
    // init engine
    uint result = Engine::init_SDL();
    if(result == Engine::ENGINE_FAILED) return 1;

    // create window
    Window::create_instance(TITLE, WIDTH, HEIGHT);

    // init image
    result = Engine::init_SDL_image();
    if(result == Engine::ENGINE_FAILED) return 1;

    // ------ testing ------ //
    
    

    // --------------------- //


    running = true;
    SDL_Event event;
    Clock::start();
    while(running){
        Clock::update();
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    running = false;
                    break;
                
            }
        }
        // std::cout << delta_time << "ms" << std::endl;

        SDL_SetRenderDrawColor(Window::instance_renderer, 255, 255, 255, 255);        
        SDL_RenderFillRect(Window::instance_renderer, NULL);

        SDL_RenderPresent(Window::instance_renderer);

    }

    Window::clean();
    Engine::clean();

    return 0;
}
