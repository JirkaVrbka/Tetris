#ifndef TETRIS_TIMER_HPP
#define TETRIS_TIMER_HPP

#include <SDL_timer.h>

class Timer {
public:
    void reset_timer() {
        stored_time = SDL_GetTicks();
    }

    bool did_time_passed(unsigned int time_to_pass) {
        return get_time_elapsed() > time_to_pass;
    }

    unsigned int get_time_elapsed() {
        return SDL_GetTicks() - stored_time;
    }

private:
    unsigned int stored_time = SDL_GetTicks();
};

#endif //TETRIS_TIMER_HPP
