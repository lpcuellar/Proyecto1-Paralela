cmake_minimum_required(VERSION 3.21)
project(proyecto1)

set(CMAKE_CXX_STANDARD 20)

find_package(SDL2 REQUIRED)
find_package(OpenMP REQUIRED)
link_libraries(OpenMP::OpenMP_CXX)

add_executable(proyecto1 main.cpp Circle.cpp Constants.cpp)
target_link_libraries(proyecto1 SDL2::SDL2main SDL2::SDL2)