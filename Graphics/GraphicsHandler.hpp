#ifndef TETRIS_GRAPHICSHANDLER_HPP
#define TETRIS_GRAPHICSHANDLER_HPP


#include <memory>
#include <SDL_render.h>
#include <functional>
#include "../Enums/Color.hpp"
#include "Layout.hpp"

typedef std::unique_ptr<SDL_Window, std::function<void(SDL_Window *)>> sdl_window_ptr;
typedef std::unique_ptr<SDL_Renderer, std::function<void(SDL_Renderer *)>> sdl_renderer_ptr;
typedef std::unique_ptr<SDL_Texture, std::function<void(SDL_Texture *)>> sdl_texture_ptr;

class GraphicsHandler {
private:
    sdl_window_ptr sdl_window;
    sdl_renderer_ptr sdl_render;
public:

    GraphicsHandler() : GraphicsHandler(640, 480) {}

    GraphicsHandler(int width, int height);

    void add_rectangle_filled(Color color, int x, int y, int w, int h) const;

    void add_rectangle_filled(Color color, const SDL_Rect &position) const;

    void add_rectangle_lines(Color color, int x, int y, int w, int h) const;

    void add_rectangle_lines(Color color, SDL_Rect &position) const;

    void add_text(const std::string &text, const Layout::TextLayout &text_layout);

    void add_button(const std::string &text, const Layout::Button &button);

    void set_viewport(const SDL_Rect &viewport) const;

    void render() const;
};


#endif //TETRIS_GRAPHICSHANDLER_HPP
