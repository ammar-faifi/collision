cmake_minimum_required(VERSION 3.0)
project(main)

# Find raylib library
find_library(RAYLIB_LIBRARY NAMES raylib PATHS ../raylib/src/)

# Find required frameworks
find_library(COREVIDEO_LIBRARY CoreVideo)
find_library(IOKIT_LIBRARY IOKit)
find_library(COCOA_LIBRARY Cocoa)
find_library(GLUT_LIBRARY GLUT)
find_library(OPENGL_LIBRARY OpenGL)

# Include raylib headers
include_directories(../raylib/src/)

# Add your source file
add_executable(main.app main.c)

# Link raylib and required frameworks
target_link_libraries(main.app ${RAYLIB_LIBRARY} ${COREVIDEO_LIBRARY} ${IOKIT_LIBRARY} ${COCOA_LIBRARY} ${GLUT_LIBRARY} ${OPENGL_LIBRARY})
