cmake_minimum_required(VERSION 3.0)
project(akimbolib)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON) 

# Debug stuff
set(CMAKE_BUILD_TYPE Debug)
add_definitions(-DDEBUG)

# Build of Freetype2 might fail without this
add_definitions(-DHAVE_FCNTL_H)

# Save every filename in akimbo/ and akimbo/ui/
FILE(GLOB AkimboSources akimbo/*.cc akimbo/ui/*.cc)

# Add Freetype2 to the project
include_directories(thirdparty/freetype/include)
add_subdirectory(thirdparty/freetype)

# Create the akimbo library and link it with necessary stuff
add_library(akimbo ${AkimboSources})
target_link_libraries(akimbo -lSDL2 -lGL -lGLEW)
target_link_libraries(akimbo freetype)

# Create a testbed for akimbo
add_executable(akimbotest test.cc)
add_dependencies(akimbotest akimbo)
target_link_libraries(akimbotest akimbo)

# Copy the resources where the binary is
FILE(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources DESTINATION ${CMAKE_BINARY_DIR})
