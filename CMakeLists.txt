cmake_minimum_required(VERSION 3.23)
project(MovieLibrary)

set(CMAKE_CXX_STANDARD 14)

add_executable(MovieLibrary main.cpp List.h MoviesException.h DataTypes.h json.hpp jsonHandler.h)
