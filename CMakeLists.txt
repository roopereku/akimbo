cmake_minimum_required(VERSION 3.0)
project(akimbo)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE AkimboSources source/*.cc)

add_library(akimbo ${AkimboSources})
target_include_directories(akimbo PUBLIC include)
target_link_libraries(akimbo SDL2 SDL2_image)

project(akimbotest)

add_executable(akimbotest test.cc)
target_link_libraries(akimbotest akimbo)
