#ifndef TETRIS_GAMEMECHANICS_HPP
#define TETRIS_GAMEMECHANICS_HPP


#include <functional>
#include "../Enums/Color.hpp"
#include "../Enums/Direction.hpp"
#include "Shapes/Shape.hpp"
#include "../Enums/Commands.hpp"

typedef std::vector<std::vector<Color>> matrix;

class GameMechanics {
private:
    const int game_matrix_width;
    const int game_matrix_height;

    const int next_piece_matrix_width;
    const int next_piece_matrix_height;

    matrix game_matrix;
    matrix next_piece_matrix;

    std::function<void(int)> score_counter;
    Shape current_shape;
    Shape next_shape;

public:

    enum class MoveState {
        OK, NOK, GAME_OVER
    };

    GameMechanics(
            int matrix_width,
            int matrix_height,
            std::function<void(int)> score_counter);

    MoveState on_action(MoveCommand action);

    const std::vector<std::vector<Color>> &get_game_matrix() const;

    const std::vector<std::vector<Color>> &get_next_piece_matrix() const;

    void reset();


private:
    MoveState move_current_piece(Direction direction);

    MoveState rotate_current_piece();

    MoveState rotate_current_piece_reverse();

    void remove_current_piece_from_matrix();

    void write_current_piece_into_matrix();

    bool is_inside_matrix(const Brick &brick) const;

    int remove_full_lines_from_matrix();

    bool can_current_piece_be_written() const;

    Shape generate_random_shape() const;

    void update_next_piece_matrix();

    static Direction get_opposite_direction(Direction direction);
};


#endif //TETRIS_GAMEMECHANICS_HPP
