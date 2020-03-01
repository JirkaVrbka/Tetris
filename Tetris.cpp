#include "Tetris.hpp"

void Tetris::periodic_move_down() {
    unsigned int break_time = game_mode == Mode::NORMAL ? 1000 - level : min_breaks;

    if (game_periodic_down_move_timer.get_time_elapsed() > std::max(min_breaks, break_time)) {
        game_periodic_down_move_timer.reset_timer();

        SDL_Event sdl_event_down;
        sdl_event_down.type = SDL_KEYDOWN;
        sdl_event_down.key.keysym.sym = SDLK_DOWN;

        SDL_PushEvent(&sdl_event_down);
    }
}

void Tetris::level_up() {
    if (game_level_up_timer.did_time_passed(1000)) {
        level++;
        game_level_up_timer.reset_timer();
    }
}

void Tetris::render() {

    graphics.add_background();
    graphics.add_game_matrix(playground.get_game_matrix());
    graphics.add_next_piece_matrix(playground.get_next_piece_matrix());

    graphics.add_level(level / 10);
    graphics.add_score(score);
    graphics.add_exit_button();

    if (game_state == GameState::GAME_OVER) {
        graphics.add_text_game_over();
        graphics.add_main_button("Restart");
    } else if (game_state == GameState::PAUSED || game_state == GameState::EXCEPTION) {
        graphics.add_main_button("Start");
        graphics.add_text_paused();
        if (game_state == GameState::EXCEPTION) {
            graphics.add_exception();
        }
    } else if (game_state == GameState::RUNNING) {
        graphics.add_main_button("Pause");
    }

    graphics.render();


    // Static framerate
    if (fps.get_time_elapsed() < 1000 / framerate) {
        SDL_Delay((1000 / framerate) - fps.get_time_elapsed());
    } else {
        fps.reset_timer();
    }
}

bool Tetris::handle_move_commands(const std::vector<MoveCommand> &commands) {
    bool is_game_over = false;
    for (const auto &command : commands) {
        if (!is_game_over) {
            is_game_over = playground.on_action(command) == GameMechanics::MoveState::GAME_OVER;
        }
    }

    return !is_game_over;
}

void Tetris::handle_control_commands(const std::vector<ControlCommand> &commands) {
    for (const auto &command : commands) {
        switch (command) {
            case ControlCommand::RUN:
                if (game_state == GameState::PAUSED || game_state == GameState::EXCEPTION) {
                    game_state = GameState::RUNNING;
                } else if (game_state == GameState::GAME_OVER) {
                    game_state = GameState::RUNNING;
                    level = 0;
                    score = 0;
                    playground.reset();
                } else if (game_state == GameState::RUNNING) {
                    game_state = GameState::PAUSED;
                }
                break;
            case ControlCommand::QUIT:
                game_state = GameState::QUIT;
                break;
            case ControlCommand::FASTER:
                game_mode = Mode::FAST;
                break;
            case ControlCommand::SLOWER:
                game_mode = Mode::NORMAL;
            default:
                break;
        }
    }
}

void Tetris::run_game() {
    fps.reset_timer();
    game_periodic_down_move_timer.reset_timer();
    game_level_up_timer.reset_timer();

    while (game_state != GameState::QUIT) {
        try {
            auto commands = eventHandler.get_commands();

            if (game_state == GameState::RUNNING) {
                // Move triggered by user
                bool is_game_ok = handle_move_commands(commands.first);

                if (!is_game_ok) {
                    game_state = GameState::GAME_OVER;
                }

                // Automatic move down
                periodic_move_down();

                // Leveling up
                level_up();
            }

            handle_control_commands(commands.second);

            // Graphics rendering
            render();

        } catch (std::invalid_argument &e) {
            game_state = GameState::EXCEPTION;
            playground.reset();
        }
    }
}

