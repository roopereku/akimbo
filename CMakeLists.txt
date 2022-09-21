cmake_minimum_required(VERSION 3.0)
project(akimbolib)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON) 

find_package(glm REQUIRED)
find_package(GLEW REQUIRED)
find_package(SDL2 REQUIRED)
find_package(Freetype REQUIRED)

# TODO The user should have to enable debug mode
set(CMAKE_BUILD_TYPE Debug)
add_definitions(-DDEBUG)

# Save every filename in akimbo/ and akimbo/ui/
FILE(GLOB AkimboSources akimbo/*.cc akimbo/ui/*.cc)

# Create the akimbo library and link it with necessary stuff
add_library(akimbo ${AkimboSources})

# Setup with freetype
target_link_libraries(akimbo ${FREETYPE_LIBRARIES})
target_include_directories(akimbo PRIVATE ${FREETYPE_INCLUDE_DIRS})

# Link necessary libraries
target_link_libraries(akimbo -lSDL2 -lGL -lGLEW)

# Create a testbed for akimbo
add_executable(akimbotest test.cc)
add_dependencies(akimbotest akimbo)
target_link_libraries(akimbotest akimbo)

# Copy the resources to where the binary is
FILE(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources DESTINATION ${CMAKE_BINARY_DIR})
