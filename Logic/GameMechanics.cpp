#include <random>
#include <set>
#include "GameMechanics.hpp"
#include "Shapes/ShapeCreator.hpp"
#include "../Enums/Commands.hpp"


GameMechanics::GameMechanics(
        int matrix_width,
        int matrix_height,
        std::function<void(int)> score_counter) : game_matrix_width(matrix_width),
                                                  game_matrix_height(matrix_height),
                                                  next_piece_matrix_width(5),
                                                  next_piece_matrix_height(4),
                                                  score_counter(std::move(score_counter)),
                                                  current_shape(generate_random_shape()),
                                                  next_shape(generate_random_shape()) {

    next_piece_matrix = std::vector<std::vector<Color>>(next_piece_matrix_width,
                                                        std::vector<Color>(next_piece_matrix_height, Colors::BLACK));
    reset();
}


GameMechanics::MoveState GameMechanics::on_action(MoveCommand action) {
    switch (action) {
        case MoveCommand::LEFT:
            return move_current_piece(Direction::LEFT);
        case MoveCommand::RIGHT:
            return move_current_piece(Direction::RIGHT);
        case MoveCommand::DOWN:
            return move_current_piece(Direction::DOWN);
        case MoveCommand::ROTATE:
            return rotate_current_piece();
        case MoveCommand::REVERSE_ROTATE:
            return rotate_current_piece_reverse();
    }
}

GameMechanics::MoveState GameMechanics::move_current_piece(Direction direction) {
    remove_current_piece_from_matrix();
    current_shape.move(direction);

    if (can_current_piece_be_written()) {
        write_current_piece_into_matrix();

        return MoveState::OK;
    } else {
        // If not a space, move back
        current_shape.move(get_opposite_direction(direction));
        write_current_piece_into_matrix();

        if (direction == Direction::DOWN) {
            int lines = remove_full_lines_from_matrix();
            score_counter(lines);

            current_shape = next_shape;
            next_shape = generate_random_shape();
            update_next_piece_matrix();

            // If generated shape does not have a space to bbe placed -> game over
            if (can_current_piece_be_written()) {
                write_current_piece_into_matrix();
            } else {
                return MoveState::GAME_OVER;
            }
        }

        return MoveState::NOK;
    }
}

GameMechanics::MoveState GameMechanics::rotate_current_piece_reverse() {
    remove_current_piece_from_matrix();
    current_shape.rotate();
    current_shape.rotate();
    current_shape.rotate();

    // Check if there is a space for move
    if (can_current_piece_be_written()) {
        write_current_piece_into_matrix();

        return MoveState::OK;
    } else {
        // If not a space, move back
        current_shape.rotate();
        write_current_piece_into_matrix();

        return MoveState::NOK;
    }
}

GameMechanics::MoveState GameMechanics::rotate_current_piece() {
    remove_current_piece_from_matrix();
    current_shape.rotate();

    // Check if there is a space for move
    if (can_current_piece_be_written()) {
        write_current_piece_into_matrix();

        return MoveState::OK;
    } else {
        // If not a space, move back
        current_shape.rotate();
        current_shape.rotate();
        current_shape.rotate();
        write_current_piece_into_matrix();

        return MoveState::NOK;
    }
}

void GameMechanics::remove_current_piece_from_matrix() {
    for (const Brick &brick : current_shape.get_bricks()) {
        if (is_inside_matrix(brick)) {
            game_matrix[brick.x][brick.y] = Colors::BLACK;
        } else {
            throw std::invalid_argument(
                    "Brick is out of matrix! X: " + std::to_string(brick.x) + ",Y: " + std::to_string(brick.y));
        }
    }
}

void GameMechanics::write_current_piece_into_matrix() {
    for (const Brick &brick : current_shape.get_bricks()) {
        game_matrix[brick.x][brick.y] = brick.color;
    }
}

Shape GameMechanics::generate_random_shape() const {
    // Random number generator
    std::random_device rd;
    std::mt19937 gen = std::mt19937(rd());
    std::uniform_int_distribution<> dis = std::uniform_int_distribution<>(0, 6);

    int random_number = dis(gen);
    return ShapeCreator::create(SHADE_TYPES[random_number], (game_matrix_width / 2), 4);
}

bool GameMechanics::is_inside_matrix(const Brick &brick) const {
    return brick.x >= 0 && brick.y >= 0 && brick.x < game_matrix_width && brick.y < game_matrix_height;
}

int GameMechanics::remove_full_lines_from_matrix() {
    std::set<int> lines_to_remove;
    for (const Brick &brick : current_shape.get_bricks()) {

        bool has_full_line = true;

        // Check for full lines for line
        for (int x = 0; x < game_matrix_width; x++) {
            if (game_matrix[x][brick.y].equals(Colors::BLACK)) {
                has_full_line = false;
                break;
            }
        }

        if (has_full_line) {
            lines_to_remove.insert(brick.y);
        }

    }

    for (int line : lines_to_remove) {
        for (int x = 0; x < game_matrix_width; x++) {
            for (int y = line - 1; y >= 0; y--) {
                game_matrix[x][y + 1] = game_matrix[x][y];
            }
        }

        for (int x = 0; x < game_matrix_width; x++) {
            game_matrix[x][0] = Colors::BLACK;
        }
    }

    return lines_to_remove.size();
}

bool GameMechanics::can_current_piece_be_written() const {
    for (const Brick &brick : current_shape.get_bricks()) {
        if (!is_inside_matrix(brick)) {
            return false;
        }

        if (!game_matrix[brick.x][brick.y].equals(Colors::BLACK)) {
            return false;
        }
    }

    return true;
}

Direction GameMechanics::get_opposite_direction(Direction direction) {
    switch (direction) {
        case Direction::UP:
            return Direction::DOWN;
        case Direction::DOWN:
            return Direction::UP;
        case Direction::LEFT:
            return Direction::RIGHT;
        case Direction::RIGHT:
            return Direction::LEFT;
    }
}

void GameMechanics::reset() {
    current_shape = generate_random_shape();
    next_shape = generate_random_shape();
    game_matrix = std::vector<std::vector<Color>>(game_matrix_width,
                                                  std::vector<Color>(game_matrix_height, Colors::BLACK));
    update_next_piece_matrix();
}

const std::vector<std::vector<Color>> &GameMechanics::get_game_matrix() const {
    return game_matrix;
}

const std::vector<std::vector<Color>> &GameMechanics::get_next_piece_matrix() const {
    return next_piece_matrix;
}

void GameMechanics::update_next_piece_matrix() {
    for (std::vector<Color> &column : next_piece_matrix) {
        for (Color &c : column) {
            c = Colors::BLACK;
        }
    }

    for (const Brick &brick : next_shape.get_bricks()) {
        next_piece_matrix[brick.x - game_matrix_width / 2 + 2][brick.y - 2] = brick.color;
    }
}
