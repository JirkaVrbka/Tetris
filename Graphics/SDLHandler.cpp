#include <SDL_image.h>
#include <SDL_ttf.h>
#include "SDLHandler.hpp"
#include "../Enums/Color.hpp"

sdl_window_ptr SDLHandler::create_window(int width, int height) {
    auto sdl_window = sdl_window_ptr(
            SDL_CreateWindow("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN),
            SDL_DestroyWindow
    );

    if (sdl_window == nullptr) {
        throw std::runtime_error("Unable to allocate SDL Window. SDL Error: " + std::string(SDL_GetError()));
    }

    return sdl_window;
}

sdl_renderer_ptr SDLHandler::create_renderer(sdl_window_ptr &window) {
    auto sdl_renderer = sdl_renderer_ptr(
            SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC),
            SDL_DestroyRenderer
    );

    if (sdl_renderer == nullptr) {
        throw std::runtime_error("Unable to allocate SDL Renderer. SDL Error: " + std::string(SDL_GetError()));
    }

    return sdl_renderer;
}

sdl_texture_ptr SDLHandler::load_text(sdl_renderer_ptr &renderer, std::string text, Color color, int font_size) {
    TTF_Font *sans = TTF_OpenFont("./../Resources/OpenSans-Regular.ttf",
                                  font_size); //this opens a font style and sets a size

    if (sans == NULL) {
        throw std::runtime_error("Unable to load fonts: " + std::string(SDL_GetError()));
    }

    SDL_Surface *text_as_surface = TTF_RenderText_Solid(sans, text.c_str(), {color.r, color.g, color.b,
                                                                             color.a});

    TTF_CloseFont(sans);
    if (text_as_surface == NULL) {
        throw std::runtime_error("Unable to create surface: " + std::string(SDL_GetError()));
    }

    auto texture = sdl_texture_ptr(
            SDL_CreateTextureFromSurface(renderer.get(), text_as_surface),
            SDL_DestroyTexture
    );

    SDL_FreeSurface(text_as_surface);

    return texture;
}
