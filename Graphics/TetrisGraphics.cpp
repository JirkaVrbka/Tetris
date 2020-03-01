#include <iomanip>
#include "TetrisGraphics.hpp"

void TetrisGraphics::add_text_game_over() {
    graphicsHandler.set_viewport(layout.playground_viewport);
    graphicsHandler.add_text("Game over", layout.information_text);
}

void TetrisGraphics::add_text_paused() {
    graphicsHandler.set_viewport(layout.playground_viewport);
    graphicsHandler.add_text("Paused", layout.information_text);
}

void TetrisGraphics::add_background() {
    graphicsHandler.set_viewport(layout.full_viewport);
    graphicsHandler.add_rectangle_filled(Colors::BLACK, layout.full_viewport);
}

void TetrisGraphics::add_score(unsigned int score) {
    std::stringstream ss;
    ss << std::setw(10) << score;
    graphicsHandler.set_viewport(layout.controller_viewport);
    graphicsHandler.add_text("Score: ", layout.score_text);
    graphicsHandler.add_text(ss.str(), layout.score_number);
}

void TetrisGraphics::add_main_button(const std::string &text) {
    graphicsHandler.set_viewport(layout.controller_viewport);
    graphicsHandler.add_button(text, layout.main_button);
}

void TetrisGraphics::add_exit_button() {
    graphicsHandler.set_viewport(layout.controller_viewport);
    graphicsHandler.add_button("Exit", layout.exit_button);
}

void TetrisGraphics::add_level(unsigned int level) {
    std::stringstream ss;
    ss << std::setw(10) << level;

    graphicsHandler.set_viewport(layout.controller_viewport);
    graphicsHandler.add_text("Level: ", layout.level_text);
    graphicsHandler.add_text(ss.str(), layout.level_number);
}

void TetrisGraphics::add_game_matrix(const std::vector<std::vector<Color>> &game_matrix) const {
    graphicsHandler.set_viewport(layout.playground_viewport);

    for (int x = 0; x < static_cast<int>(game_matrix.size()); x++) {
        // Starts from 5 to appear that brick falls from top
        for (int y = layout.playground_hidden_top; y < static_cast<int>(game_matrix[x].size()); y++) {
            Color borderColor = game_matrix[x][y].equals(Colors::BLACK) ? Colors::GRAY : Colors::WHITE;

            graphicsHandler.add_rectangle_lines(
                    borderColor,
                    x * layout.brick_size,
                    (y - layout.playground_hidden_top) * layout.brick_size,
                    layout.brick_size,
                    layout.brick_size);
            graphicsHandler.add_rectangle_filled(
                    game_matrix[x][y],
                    (x * layout.brick_size) + layout.brick_border,
                    ((y - layout.playground_hidden_top) * layout.brick_size) + layout.brick_border,
                    layout.brick_size - layout.brick_border * 2,
                    layout.brick_size - layout.brick_border * 2);
        }
    }
}

void TetrisGraphics::render() {
    graphicsHandler.render();
}

void TetrisGraphics::add_exception() {
    graphicsHandler.set_viewport(layout.controller_viewport);
    graphicsHandler.add_text("We are sorry, an inner exception occurred. We reset playground.",
                             layout.exception_message);
}

void TetrisGraphics::add_next_piece_matrix(const std::vector<std::vector<Color>> &next_piece_matrix) const {

    graphicsHandler.set_viewport(layout.next_piece_viewport);

    for (int x = 0; x < static_cast<int>(next_piece_matrix.size()); x++) {
        // Starts from 5 to appear that brick falls from top
        for (int y = 0; y < static_cast<int>(next_piece_matrix[x].size()); y++) {
            Color borderColor = next_piece_matrix[x][y].equals(Colors::BLACK) ? Colors::GRAY : Colors::WHITE;

            graphicsHandler.add_rectangle_lines(
                    borderColor,
                    x * layout.brick_size,
                    y * layout.brick_size,
                    layout.brick_size,
                    layout.brick_size);
            graphicsHandler.add_rectangle_filled(
                    next_piece_matrix[x][y],
                    (x * layout.brick_size) + layout.brick_border,
                    (y * layout.brick_size) + layout.brick_border,
                    layout.brick_size - layout.brick_border * 2,
                    layout.brick_size - layout.brick_border * 2);
        }
    }
}
