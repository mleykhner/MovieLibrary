cmake_minimum_required(VERSION 3.23)
project(MovieLibrary)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory("/Users/mleykhner/Documents/Курсовая 3 сем/MovieLibrary/nfd")
set_target_properties(nfd PROPERTIES LINKER_LANGUAGE CXX)
add_executable(MovieLibrary main.cpp List.h MoviesException.h DataTypes.h json.hpp jsonHandler.h)
target_link_libraries(MovieLibrary PRIVATE nfd)
