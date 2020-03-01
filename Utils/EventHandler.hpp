#ifndef TETRIS_EVENTHANDLER_HPP
#define TETRIS_EVENTHANDLER_HPP


#include <vector>
#include "../Graphics/Layout.hpp"
#include "../Enums/Commands.hpp"

struct EventHandler {
private:
    const Layout layout;
public:
    explicit EventHandler(Layout layout) : layout(std::move(layout)) {}

    std::pair<std::vector<MoveCommand>, std::vector<ControlCommand>> get_commands();
};


#endif //TETRIS_EVENTHANDLER_HPP
