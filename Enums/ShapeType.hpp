#ifndef TETRIS_SHAPETYPE_HPP
#define TETRIS_SHAPETYPE_HPP

enum class ShapeType {
    LINE, SQUARE, T, L, OPP_L, Z, OPP_Z
};

static const ShapeType SHADE_TYPES[] = {ShapeType::LINE, ShapeType::SQUARE, ShapeType::T, ShapeType::L,
                                        ShapeType::OPP_L, ShapeType::Z, ShapeType::OPP_Z};
#endif //TETRIS_SHAPETYPE_HPP
