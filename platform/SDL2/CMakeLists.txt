cmake_minimum_required(VERSION 3.5)
project(akimboSDL2)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)

file(GLOB Sources *.cc)

add_library(akimboSDL2 ${Sources})
target_link_libraries(akimboSDL2 libakimbo SDL2)
target_include_directories(akimboSDL2 PUBLIC include)
