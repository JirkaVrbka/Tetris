#ifndef TETRIS_SHAPE_HPP
#define TETRIS_SHAPE_HPP

#include "Brick.hpp"
#include "../../Enums/Direction.hpp"

typedef Brick brick_array[4];

class Shape {
private:
    brick_array bricks;
    bool rotatable;

public:
    Shape(Brick centerBrick, Brick b2, Brick b3, Brick b4, bool rotatable = true) : bricks{centerBrick, b2, b3, b4},
                                                                                    rotatable(rotatable) {}

    void move(Direction direction) {
        for (Brick &brick : bricks) {
            brick.move(direction);
        }
    }

    void rotate() {
        if (rotatable) {
            int center_x = bricks[0].x;
            int center_y = bricks[0].y;

            for (int i = 1; i < 4; i++) {
                int diff_x = center_x - bricks[i].x;
                int diff_y = center_y - bricks[i].y;

                bricks[i].x = center_x - diff_y;
                bricks[i].y = center_y + diff_x;
            }
        }
    }

    brick_array &get_bricks() {
        return bricks;
    }

    const brick_array &get_bricks() const {
        return bricks;
    }
};

#endif //TETRIS_SHAPE_HPP
