#ifndef TETRIS_SDLHANDLER_HPP
#define TETRIS_SDLHANDLER_HPP

#include <memory>
#include <SDL.h>
#include <SDL_timer.h>
#include <functional>
#include "../Enums/Color.hpp"

typedef std::unique_ptr<SDL_Window, std::function<void(SDL_Window *)>> sdl_window_ptr;
typedef std::unique_ptr<SDL_Renderer, std::function<void(SDL_Renderer *)>> sdl_renderer_ptr;
typedef std::unique_ptr<SDL_Texture, std::function<void(SDL_Texture *)>> sdl_texture_ptr;

/**
 * Handler for SDL
 * Wraps C SDL pointers into C++ unique pointers (with destructors) to better maintenance
 */
class SDLHandler {
public:
    static sdl_window_ptr create_window(int width, int height);

    static sdl_renderer_ptr create_renderer(sdl_window_ptr &window);

    static sdl_texture_ptr load_text(sdl_renderer_ptr &renderer, std::string text, Color color, int font_size = 24);
};

#endif //TETRIS_SDLHANDLER_HPP
