cmake_minimum_required(VERSION 3.23)
project(MovieLibrary)

set(CMAKE_CXX_STANDARD 14)

add_executable(MovieLibrary main.cpp movieScroller.h DataArrays.h MoviesException.h DataTypes.h json.hpp jsonHandler.h TextBox.cpp TextBox.h TextButton.cpp TextButton.h Functions.h)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(MovieLibrary sfml-system sfml-window sfml-graphics sfml-audio sfml-network)