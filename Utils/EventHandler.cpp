#include <SDL_events.h>
#include "EventHandler.hpp"
#include "../Enums/Commands.hpp"

std::pair<std::vector<MoveCommand>, std::vector<ControlCommand>> EventHandler::get_commands() {
    std::pair<std::vector<MoveCommand>, std::vector<ControlCommand>> commands;
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        // User requests quit
        if (e.type == SDL_QUIT) {
            commands.second.push_back(ControlCommand::QUIT);
        } else if (e.type == SDL_KEYDOWN) {
            // Select action based on key press
            switch (e.key.keysym.sym) {
                case SDLK_f:
                case SDL_SCANCODE_KP_0:
                    commands.first.push_back(MoveCommand::REVERSE_ROTATE);
                    break;
                case SDLK_w:
                case SDLK_UP:
                    commands.first.push_back(MoveCommand::ROTATE);
                    break;
                case SDLK_s:
                case SDLK_DOWN:
                    commands.first.push_back(MoveCommand::DOWN);
                    break;
                case SDLK_a:
                case SDLK_LEFT:
                    commands.first.push_back(MoveCommand::LEFT);
                    break;
                case SDLK_d:
                case SDLK_RIGHT:
                    commands.first.push_back(MoveCommand::RIGHT);
                    break;
                case SDLK_SPACE:
                    commands.second.push_back(ControlCommand::FASTER);
                    break;
                case SDLK_q:
                    commands.second.push_back(ControlCommand::QUIT);
                    break;
                case SDLK_p:
                case SDLK_RETURN:
                    commands.second.push_back(ControlCommand::RUN);
                    break;
            }
        } else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_SPACE) {
            commands.second.push_back(ControlCommand::SLOWER);
        } else if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
            if (e.button.x >= layout.exit_button.position.x + layout.controller_viewport.x &&
                e.button.x <=
                layout.exit_button.position.x + layout.controller_viewport.x + layout.exit_button.position.w &&
                e.button.y >= layout.exit_button.position.y + layout.controller_viewport.y &&
                e.button.y <=
                layout.exit_button.position.y + layout.controller_viewport.y + layout.exit_button.position.h
                    ) {
                commands.second.push_back(ControlCommand::QUIT);
            } else if (e.button.x >= layout.main_button.position.x + layout.controller_viewport.x &&
                       e.button.x <=
                       layout.main_button.position.x + layout.controller_viewport.x + layout.main_button.position.w &&
                       e.button.y >= layout.main_button.position.y + layout.controller_viewport.y &&
                       e.button.y <=
                       layout.main_button.position.y + layout.controller_viewport.y + layout.main_button.position.h) {
                commands.second.push_back(ControlCommand::RUN);
            }
        }
    }

    return commands;
}
