# Cmake version
cmake_minimum_required(VERSION 3.10)

# CFLAG
set(CMAKE_CXX_STANDARD 14)
set(LINK_FLAG dl pthread X11 Xrandr Xinerama Xxf86vm Xcursor)
set(PROJECT ng-ui)

# Include header
include_directories(include)
include_directories(lib)

#For the static library:
file(GLOB SOURCES "src/*.cpp" "src/*.c")

# Project
project(${PROJECT})
add_executable(${PROJECT} ${SOURCES})
target_link_libraries(${PROJECT} ${CMAKE_SOURCE_DIR}/lib/libglfw3.a ${LINK_FLAG})