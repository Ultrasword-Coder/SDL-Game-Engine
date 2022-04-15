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

#include "src/engine/engine.hpp"
#include "src/engine/window.hpp"
#include "src/engine/clock.hpp"
#include "src/engine/keyboard.hpp"
#include "src/engine/filehandler.hpp"
#include "src/engine/draw.hpp"
#include "src/engine/physics.hpp"
#include "src/engine/world.hpp"

unsigned int WIDTH = 800, HEIGHT = 600;
const char *TITLE = "Template";

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
    SDL_Log("[MAIN] loaded window");

    // ------------------------------ testing ------------------------------------------------ //

    Graphics::Texture *tex = ImageHandler::load_image(Window::instance_renderer, "assets/unknown.png");
    Rect pos;
    pos.x = 0;
    pos.y = 0;
    pos.w = 100;
    pos.h = 100;

    Color white;
    white.r = 255;
    white.g = 255;
    white.b = 255;
    white.a = 255;

    SDL_Log("[MAIN] loaded image");

    Graphics::Texture *sheet = ImageHandler::load_image(Window::instance_renderer, "assets/tilemap.png");
    Graphics::SpriteSheet spritesheet(sheet, 10 * 10, 16, 16, 0, 0);
    spritesheet.create();

    // testing chunks
    World::World world;
    World::Chunk *chunk;
    World::Tile tile;

    chunk = world.make_template_chunk(0, 0);

    // error
    tile = world.create_tile(0, 0, "assets/unknown.png");

    World::set_tile_at(chunk, &tile);

    // --------------------------------------------------------------------------------------- //

    SDL_Event event;
    Clock::start();
    while (Window::running)
    {
        Clock::update();
        handleEvents();
        // std::cout << delta_time << "ms" << std::endl;
        SDL_RenderClear(Window::instance_renderer);

        if (Keyboard::is_key_pressed(SDLK_a))
            pos.x -= 5;
        if (Keyboard::is_key_pressed(SDLK_d))
            pos.x += 5;
        if (Keyboard::is_key_pressed(SDLK_w))
            pos.y -= 5;
        if (Keyboard::is_key_pressed(SDLK_s))
            pos.y += 5;

        // rescale testing
        if (Keyboard::is_key_pressed(SDLK_LSHIFT) && Keyboard::is_key_pressed(SDLK_SPACE))
        {
            pos.w -= 5;
            pos.h -= 5;
        }
        else if (Keyboard::is_key_pressed(SDLK_SPACE))
        {
            pos.w += 5;
            pos.h += 5;
        }
        // SDL_Log("%dms", Clock::delta_time);

        Draw::fill(&white);

        // render world
        world.render_chunks(0, 0);

        // test render
        for (int i = 0; i < (int)spritesheet.get_count(); i++)
            Draw::render_sprite_object(&spritesheet, &spritesheet.sprite_at(i)->area, &spritesheet.sprite_at(i)->area);

        Draw::blit(tex, &pos);

        SDL_RenderPresent(Window::instance_renderer);
    }

    ImageHandler::clean();
    Window::clean();
    Engine::clean();

    return 0;
}
