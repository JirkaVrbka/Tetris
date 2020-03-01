#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include "Tetris.hpp"

int main() {
    if (SDL_Init(SDL_INIT_TIMER) != 0) {
        std::cout << "We are sorry but we were not able to init SDL (graphics)" << std::endl;
    }

    if (TTF_Init() != 0) {
        std::cout << "We are sorry but we were not able to init TTF (fonds)" << std::endl;
        SDL_Quit();
    }


    Tetris tetris;
    try {
        tetris.run_game();
    } catch (std::runtime_error &e) {
        std::cout << "We are sorry but inner error occurred and we were not able to resolve it." << std::endl;
        std::cerr << e.what() << std::endl;
    }

    SDL_Quit();
    TTF_Quit();
    return 0;
}