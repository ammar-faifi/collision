cmake_minimum_required(VERSION 3.0)
project(my_app)

# Find raylib library
find_library(RAYLIB_LIBRARY NAMES raylib PATHS /path/to/raylib/lib)

# Find required frameworks
find_library(COREVIDEO_LIBRARY CoreVideo)
find_library(IOKIT_LIBRARY IOKit)
find_library(COCOA_LIBRARY Cocoa)
find_library(GLUT_LIBRARY GLUT)
find_library(OPENGL_LIBRARY OpenGL)

# Include raylib headers
include_directories(/path/to/raylib/include)

# Add your source file
add_executable(my_app my_app.c)

# Link raylib and required frameworks
target_link_libraries(my_app ${RAYLIB_LIBRARY} ${COREVIDEO_LIBRARY} ${IOKIT_LIBRARY} ${COCOA_LIBRARY} ${GLUT_LIBRARY} ${OPENGL_LIBRARY})
