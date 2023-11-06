cmake_minimum_required(VERSION 3.5)
project(akimbo)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(libakimbo)
add_subdirectory(platform/SDL2)

add_executable(akimbotest test.cc)
target_link_libraries(akimbotest libakimbo akimboSDL2)
