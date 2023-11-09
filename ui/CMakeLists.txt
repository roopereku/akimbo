cmake_minimum_required(VERSION 3.5)
project(akimboui)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)

file(GLOB Sources *.cc)

add_library(akimboui ${Sources})
target_link_libraries(akimboui PUBLIC libakimbo)
target_include_directories(akimboui PUBLIC include)
