#ifndef TETRIS_TETRIS_HPP
#define TETRIS_TETRIS_HPP

#include <SDL.h>
#include <iostream>
#include "Graphics/TetrisGraphics.hpp"
#include "Logic/GameMechanics.hpp"
#include "Utils/Timer.hpp"
#include "Enums/Mode.hpp"
#include "Enums/GameState.hpp"
#include "Utils/EventHandler.hpp"

class Tetris {
private:
    Layout layout;
    EventHandler eventHandler = EventHandler(layout);
    TetrisGraphics graphics = TetrisGraphics(layout);
    GameMechanics playground = GameMechanics(
            10,
            25,
            [&s = score](int l) { s += l * 40 + l * l * 10; });

    GameState game_state = GameState::PAUSED;
    Mode game_mode = Mode::NORMAL;

    unsigned int score = 0;
    unsigned int level = 0;
    const unsigned int framerate = 60;
    const unsigned int min_breaks = 5;

    Timer fps;
    Timer game_periodic_down_move_timer;
    Timer game_level_up_timer;
public:
    void run_game();

private:
    /**
     * Send down event in periodic time (1000 - level) mills
     */
    void periodic_move_down();

    /**
     * Rise level by 1 every 1000 mills
     */
    void level_up();

    void render();

    /**
     * Send move commands into playground
     * @param commands commands to be done
     * @return true if game is ok, false is game should be over
     */
    bool handle_move_commands(const std::vector<MoveCommand> &commands);

    void handle_control_commands(const std::vector<ControlCommand> &commands);

};


#endif //TETRIS_TETRIS_HPP
