cmake_minimum_required(VERSION 3.0)
project(akimbolib)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

FILE(GLOB AkimboSources akimbo/*.cc akimbo/ui/*.cc)

add_library(akimbo ${AkimboSources})
target_link_libraries(akimbo -lSDL2 -lGL -lGLEW)

add_executable(akimbotest test.cc)
add_dependencies(akimbotest akimbo)
target_link_libraries(akimbotest akimbo)

FILE(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources DESTINATION ${CMAKE_BINARY_DIR})
