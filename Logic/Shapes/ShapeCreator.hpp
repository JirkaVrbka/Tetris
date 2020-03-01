#ifndef TETRIS_SHAPECREATOR_HPP
#define TETRIS_SHAPECREATOR_HPP

#include "Shape.hpp"
#include "../../Enums/ShapeType.hpp"

class ShapeCreator {
public:
    // Returns Shape constructed by its type
    static Shape create(ShapeType type, int init_x = 0, int init_y = 0) {
        switch (type) {
            case ShapeType::L:
                return {
                        Brick(init_x, init_y, Colors::BLUE),
                        Brick(init_x + 1, init_y, Colors::BLUE),
                        Brick(init_x, init_y - 1, Colors::BLUE),
                        Brick(init_x, init_y - 2, Colors::BLUE)};
            case ShapeType::OPP_L:
                return {
                        Brick(init_x, init_y, Colors::RED),
                        Brick(init_x - 1, init_y, Colors::RED),
                        Brick(init_x, init_y - 1, Colors::RED),
                        Brick(init_x, init_y - 2, Colors::RED)};
            case ShapeType::T:
                return {
                        Brick(init_x, init_y, Colors::GREEN),
                        Brick(init_x - 1, init_y, Colors::GREEN),
                        Brick(init_x + 1, init_y, Colors::GREEN),
                        Brick(init_x, init_y - 1, Colors::GREEN)};
            case ShapeType::Z:
                return {
                        Brick(init_x, init_y, Colors::YELLOW),
                        Brick(init_x - 1, init_y, Colors::YELLOW),
                        Brick(init_x, init_y - 1, Colors::YELLOW),
                        Brick(init_x + 1, init_y - 1, Colors::YELLOW)};
            case ShapeType::OPP_Z:
                return {
                        Brick(init_x, init_y, Colors::PINK),
                        Brick(init_x + 1, init_y, Colors::PINK),
                        Brick(init_x, init_y - 1, Colors::PINK),
                        Brick(init_x - 1, init_y - 1, Colors::PINK)};
            case ShapeType::SQUARE:
                return {
                        Brick(init_x, init_y, Colors::AZURE),
                        Brick(init_x + 1, init_y, Colors::AZURE),
                        Brick(init_x, init_y + 1, Colors::AZURE),
                        Brick(init_x + 1, init_y + 1, Colors::AZURE),
                        false};
            case ShapeType::LINE:
                return {
                        Brick(init_x, init_y, Colors::PURPLE),
                        Brick(init_x, init_y + 1, Colors::PURPLE),
                        Brick(init_x, init_y - 1, Colors::PURPLE),
                        Brick(init_x, init_y - 2, Colors::PURPLE)};

        }
    }
};

#endif //TETRIS_SHAPECREATOR_HPP
