#ifndef TETRIS_LAYOUT_HPP
#define TETRIS_LAYOUT_HPP

#include <SDL_rect.h>
#include "../Enums/Color.hpp"
#include <string>
#include <utility>

class Layout {
public:
    class TextLayout {
    public:
        const SDL_Rect position;
        const Color color;
        const int font_size;

        TextLayout(Color color, int font_size, int x, int y, int w, int h) : position({x, y, w, h}), color(color),
                                                                             font_size(font_size) {}
    };

    class Button {
    public:
        const SDL_Rect position;
        const Color color;
        TextLayout text_layout;

        Button(SDL_Rect position, Color color, TextLayout text) : position(position), color(color),
                                                                  text_layout(std::move(text)) {}
    };

    const int window_height = 645;
    const int window_width = 750;
    const SDL_Rect full_viewport{0, 0, window_width, window_height};

    // Playground layout
    const SDL_Rect playground_viewport{40, 20, window_width * 1 / 2, window_height};
    const SDL_Rect next_piece_viewport{window_width * 1 / 2, 400, 200, 200};
    const int brick_size = 30;
    const int brick_border = 1;
    const int playground_hidden_top = 5;

    const TextLayout information_text = TextLayout(Colors::YELLOW, 52, 3, 3, 140, 32);


    // Controller layout
    const SDL_Rect controller_viewport{window_width * 1 / 2, 0, window_width * 1 / 2, window_height};

    const TextLayout score_text = TextLayout(Colors::YELLOW, 52, 3, 3, 80, 32);
    const TextLayout score_number = TextLayout(Colors::YELLOW, 52, 90, 3, 90, 32);

    const TextLayout level_text = TextLayout(Colors::YELLOW, 24, 3, 36, 65, 24);
    const TextLayout level_number = TextLayout(Colors::YELLOW, 24, 90, 36, 90, 24);

    const TextLayout exception_message = TextLayout(Colors::RED, 24, 0, window_height - 40, 360, 24);

    const Button main_button = Button({100, 100, 200, 60}, Colors::YELLOW,
                                      TextLayout(Colors::BLACK, 32, 150, 105, 100, 50));
    const Button exit_button = Button({100, 200, 200, 60}, Colors::YELLOW,
                                      TextLayout(Colors::BLACK, 32, 155, 205, 90, 50));

};

#endif //TETRIS_LAYOUT_HPP
