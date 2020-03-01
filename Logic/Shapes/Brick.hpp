#ifndef TETRIS_BRICK_HPP
#define TETRIS_BRICK_HPP

#include "../../Enums/Color.hpp"
#include "../../Enums/Direction.hpp"

class Brick {
public:
    int x;
    int y;
    Color color;

    Brick(int x, int y, const Color &color) : x(x), y(y), color(color) {}

    void move(Direction direction) {
        switch (direction) {
            case Direction::DOWN:
                y++;
                break;
            case Direction::LEFT:
                x--;
                break;
            case Direction::RIGHT:
                x++;
                break;
            case Direction::UP:
                y--;
                break;
        }
    }

};

#endif //TETRIS_BRICK_HPP
