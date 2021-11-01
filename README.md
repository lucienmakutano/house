# House

This an implementation of 

## Technologies
* [OpenGL](https://www.opengl.org)
* [GLEW](http://glew.sourceforge.net)
* [GLFW](https://www.glfw.org/)

## How to run the project
### Windows
use Visual Studio to run the project

### Linux
#### Requirements
* GL
* GLU
* glfw3
* X11
* Xxf86vm
* Xrandr
* pthread
* Xi
* dl 
* Xinerama
* Xcursor
* assimp

Use cmake to run the project. Make sure you have Makefile.txt
You might have to include `glad.c` depending on your setup
```cmake
cmake_minimum_required(VERSION 3.20)
project(house)

set(CMAKE_CXX_STANDARD 14)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

set(SOURCE_FILES glad.c main.cpp)

add_executable(house ${SOURCE_FILES})

target_link_libraries(house GL GLU glfw3 X11 Xxf86vm Xrandr pthread Xi dl Xinerama Xcursor assimp)
```