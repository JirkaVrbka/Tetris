#include "GraphicsHandler.hpp"
#include "SDLHandler.hpp"

GraphicsHandler::GraphicsHandler(int width, int height) {
    sdl_window = SDLHandler::create_window(width, height);
    sdl_render = SDLHandler::create_renderer(sdl_window);
}

void GraphicsHandler::add_rectangle_filled(Color color, int x, int y, int w, int h) const {
    SDL_Rect rect = SDL_Rect{x, y, w, h};
    add_rectangle_filled(color, rect);
}

void GraphicsHandler::add_rectangle_filled(Color color, const SDL_Rect &position) const {
    SDL_SetRenderDrawColor(sdl_render.get(), color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(sdl_render.get(), &position);
}

void GraphicsHandler::add_rectangle_lines(Color color, int x, int y, int w, int h) const {
    SDL_Rect rect = {x, y, w, h};
    add_rectangle_lines(color, rect);
}

void GraphicsHandler::add_rectangle_lines(Color color, SDL_Rect &position) const {
    SDL_SetRenderDrawColor(sdl_render.get(), color.r, color.g, color.b, color.a);
    SDL_RenderDrawRect(sdl_render.get(), &position);
}

void GraphicsHandler::add_text(const std::string &text, const Layout::TextLayout &text_layout) {
    SDL_RenderCopy(sdl_render.get(),
                   SDLHandler::load_text(sdl_render, text, text_layout.color, text_layout.font_size).get(), NULL,
                   &text_layout.position);
}

void GraphicsHandler::add_button(const std::string &text, const Layout::Button &button) {
    add_rectangle_filled(button.color, button.position);
    add_text(text, button.text_layout);
}

void GraphicsHandler::set_viewport(const SDL_Rect &viewport) const {
    SDL_RenderSetViewport(sdl_render.get(), &viewport);
}

void GraphicsHandler::render() const {
    SDL_RenderPresent(sdl_render.get());
    SDL_RenderClear(sdl_render.get());
}
