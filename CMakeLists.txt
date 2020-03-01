cmake_minimum_required(VERSION 3.5)
project(Tetris)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Wextra -pedantic -Wold-style-cast -Werror")

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})

set(SOURCE_FILES main.cpp Graphics/GraphicsHandler.hpp Graphics/GraphicsHandler.cpp Graphics/SDLHandler.cpp Graphics/SDLHandler.hpp Tetris.cpp Tetris.hpp Graphics/TetrisGraphics.cpp Graphics/TetrisGraphics.hpp Enums/Color.hpp Logic/Shapes/Brick.hpp Logic/Shapes/Shape.hpp Enums/ShapeType.hpp Logic/Shapes/ShapeCreator.hpp Logic/GameMechanics.cpp Logic/GameMechanics.hpp Utils/Timer.hpp Enums/Direction.hpp Enums/GameState.hpp Enums/Mode.hpp Utils/EventHandler.cpp Utils/EventHandler.hpp Graphics/Layout.hpp Enums/Commands.hpp)

configure_file(Resources/OpenSans-Regular.ttf ${CMAKE_CURRENT_BINARY_DIR}/Resources/OpenSans-Regular.ttf COPYONLY)
add_executable(tetris ${SOURCE_FILES})
target_link_libraries(tetris ${SDL2_LIBRARIES} SDL2_ttf SDL2_image)