#include <iostream>

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

#include "src/engine.hpp"
#include "src/window.hpp"
#include "src/clock.hpp"
#include "src/keyboard.hpp"
#include "src/texture.hpp"
#include "src/filehandler.hpp"

unsigned int WIDTH = 800, HEIGHT = 600;
const char *TITLE = "osu! but scam";

bool output_event = false;
SDL_Event event;

void handleEvents()
{
    while (SDL_PollEvent(&event))
    {
        // window events!
        // will output lots of random stuff
        if (event.type == SDL_WINDOWEVENT && output_event)
        {
            switch (event.window.event)
            {
            case SDL_WINDOWEVENT_SHOWN:
                SDL_Log("Window was shown!\n");
                break;
            case SDL_WINDOWEVENT_HIDDEN:
                SDL_Log("Window was hidden!\n");
                break;
            case SDL_WINDOWEVENT_EXPOSED:
                SDL_Log("Window was exposed!\n");
                break;
            case SDL_WINDOWEVENT_MOVED:
                SDL_Log("Window was moved!\n");
                break;
            case SDL_WINDOWEVENT_RESIZED:
                SDL_Log("Window was resized!\n");
                break;
            case SDL_WINDOWEVENT_SIZE_CHANGED:
                SDL_Log("Window was resized!\n");
                break;
            case SDL_WINDOWEVENT_MINIMIZED:
                SDL_Log("Window was minimized!\n");
                break;
            case SDL_WINDOWEVENT_MAXIMIZED:
                SDL_Log("Widnow was maximized!\n");
                break;
            case SDL_WINDOWEVENT_RESTORED:
                SDL_Log("Window was restored!\n");
                break;
            case SDL_WINDOWEVENT_ENTER:
                SDL_Log("Mouse entered window!\n");
                break;
            case SDL_WINDOWEVENT_LEAVE:
                SDL_Log("Mouse leaved window!\n");
                break;
            case SDL_WINDOWEVENT_FOCUS_GAINED:
                SDL_Log("Window gained keyboard focus!\n");
                break;
            case SDL_WINDOWEVENT_FOCUS_LOST:
                SDL_Log("Window lost focus!\n");
                break;
            case SDL_WINDOWEVENT_CLOSE:
                SDL_Log("Window closed!\n");
                break;
            default:
                SDL_Log("Got unhandled event!\n");
                break;
            }
        }
        else if (event.type == SDL_KEYDOWN)
        {
            Keyboard::key_pressed(event.key.keysym.sym);
        }
        else if (event.type == SDL_KEYUP)
        {
            Keyboard::key_release(event.key.keysym.sym);
        }
        else if (event.type == SDL_QUIT)
        {
            Window::running = false;
        }
    }
}

int main(int argc, char *argv[])
{
    // init engine
    uint result = Engine::init_SDL();
    if (result == Engine::ENGINE_FAILED)
        return 1;
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");

    // create window
    Window::create_instance(TITLE, WIDTH, HEIGHT);

    // init image
    result = Engine::init_SDL_image();
    if (result == Engine::ENGINE_FAILED)
        return 1;

    // turn running on to when errors occur, immediately exit
    Window::running = true;

    // ------ testing ------ //

    Texture *tex = ImageHandler::load_image(Window::instance_renderer, "skins/unknown.png");
    Rect *pos = tex->get_rect();

    Color white;
    white.r = 255;
    white.g = 255;
    white.b = 255;
    white.a = 255;

    // --------------------- //
    SDL_Event event;
    Clock::start();
    while (Window::running)
    {
        Clock::update();
        handleEvents();
        // std::cout << delta_time << "ms" << std::endl;
        SDL_RenderClear(Window::instance_renderer);

        // SDL_Log("%dms", Clock::delta_time);

        Window::fill(&white);
        Window::blit(tex, pos);

        SDL_RenderPresent(Window::instance_renderer);
    }

    ImageHandler::clean();
    Window::clean();
    Engine::clean();

    return 0;
}
