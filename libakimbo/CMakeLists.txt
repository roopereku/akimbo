cmake_minimum_required(VERSION 3.5)
project(libakimbo)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)

file(GLOB Sources *.cc)

add_library(libakimbo ${Sources})
target_include_directories(libakimbo PUBLIC include)
