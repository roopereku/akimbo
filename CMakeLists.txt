cmake_minimum_required(VERSION 3.0)
project(akimbo)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE AkimboSources source/*.cc)
add_library(akimbo ${AkimboSources})
target_include_directories(akimbo PUBLIC include)
target_link_libraries(akimbo SDL2)

project(akimbotest)

add_executable(akimbotest test.cc)
target_link_libraries(akimbotest akimbo)
