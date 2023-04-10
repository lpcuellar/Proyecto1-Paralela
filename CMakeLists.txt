cmake_minimum_required(VERSION 3.21)
project(proyecto1)

set(CMAKE_CXX_STANDARD 20)

add_executable(proyecto1 main.cpp Circle.cpp Constants.cpp)
add_executable(proyecto1_par main_par.cpp Circle.cpp Constants.cpp)

find_package(SDL2 REQUIRED)
find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries(proyecto1 PUBLIC OpenMP::OpenMP_CXX)
    target_link_libraries(proyecto1_par PUBLIC OpenMP::OpenMP_CXX)
endif()

target_link_libraries(proyecto1 PUBLIC SDL2::SDL2main SDL2::SDL2)
target_link_libraries(proyecto1_par PUBLIC SDL2::SDL2main SDL2::SDL2)






