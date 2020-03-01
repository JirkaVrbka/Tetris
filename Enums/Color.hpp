#ifndef TETRIS_COLOR_HPP
#define TETRIS_COLOR_HPP

#include <SDL_quit.h>

class Color {
public:
    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint8 a;

    Color(Uint8 r,
          Uint8 g,
          Uint8 b,
          Uint8 a = 0xFF) : r(r), g(g), b(b), a(a) {};

    bool equals(const Color &other) const {
        return r == other.r && g == other.g && b == other.b && a == other.a;
    }

};

namespace Colors {

    static const Color RED{0xFF, 0, 0};
    static const Color BLUE{0, 0, 0xFF};
    static const Color GREEN{0, 0xFF, 0};
    static const Color BLACK{0, 0, 0};
    static const Color YELLOW{0xFF, 0xFF, 0};
    static const Color PINK{0xFF, 0, 0xFF};
    static const Color AZURE{0, 0xFF, 0xFF};
    static const Color WHITE{0xFF, 0xFF, 0xFF};
    static const Color PURPLE{0x77, 0, 0xB3};
    static const Color GRAY{0x20, 0x20, 0x20};
}

#endif //TETRIS_COLOR_HPP
