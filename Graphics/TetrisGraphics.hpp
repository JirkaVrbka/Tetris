#ifndef TETRIS_TETRISGRAPHICS_HPP
#define TETRIS_TETRISGRAPHICS_HPP

#include <vector>
#include "Layout.hpp"
#include "GraphicsHandler.hpp"

/// Class handling graphics for tetris
class TetrisGraphics {
private:
    const Layout layout;

    GraphicsHandler graphicsHandler = GraphicsHandler(layout.window_width, layout.window_height);
public:
    explicit TetrisGraphics(Layout layout) : layout(std::move(layout)) {}

    void add_text_game_over();

    void add_text_paused();

    void add_background();

    void add_exception();

    void add_score(unsigned int score);

    void add_main_button(const std::string &text);

    void add_exit_button();

    void add_level(unsigned int level);

    void add_game_matrix(const std::vector<std::vector<Color>> &game_matrix) const;

    void add_next_piece_matrix(const std::vector<std::vector<Color>> &next_piece_matrix) const;

    void render();
};


#endif //TETRIS_TETRISGRAPHICS_HPP
