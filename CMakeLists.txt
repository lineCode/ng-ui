# Cmake version
cmake_minimum_required(VERSION 3.10)

# CFLAG
set(CMAKE_CXX_STANDARD 14)
set(LINK_FLAG dl pthread X11 Xrandr Xinerama Xxf86vm Xcursor)
set(PROJECT ng-ui)
set(PROJECT_DEBUG debug)

# Include header
include_directories(include)
include_directories(lib)

#For the static library:
file(GLOB SOURCES "src/*.cpp" "src/*.c")

# Project
project(${PROJECT})
add_executable(${PROJECT} ${SOURCES})
target_link_libraries(${PROJECT} ${CMAKE_SOURCE_DIR}/lib/libglfw3.a ${LINK_FLAG})

# Debug
project(${PROJECT_DEBUG})
add_executable(${PROJECT_DEBUG} ${SOURCES})
target_link_libraries(${PROJECT_DEBUG} ${CMAKE_SOURCE_DIR}/lib/libglfw3.a ${LINK_FLAG})

# Run Debug
target_compile_definitions(${PROJECT_DEBUG} PUBLIC DEBUG_MEMORY)
add_custom_target(run
    COMMAND ${PROJECT_DEBUG}
    DEPENDS ${PROJECT_DEBUG}
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)