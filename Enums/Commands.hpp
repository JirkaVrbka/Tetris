#ifndef TETRIS_COMMANDS_HPP
#define TETRIS_COMMANDS_HPP

enum class MoveCommand {
    LEFT, RIGHT, DOWN, ROTATE, REVERSE_ROTATE
};
enum class ControlCommand {
    RUN, QUIT, FASTER, SLOWER
};

#endif //TETRIS_COMMANDS_HPP
