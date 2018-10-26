# Cmake version
cmake_minimum_required(VERSION 3.0)

# CFLAG
set(CMAKE_CXX_STANDARD 14)
#set(LINK_FLAG dl pthread X11 Xrandr Xinerama Xxf86vm Xcursor)
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
    COMMAND ${PROJECT_DEBUG} ".."
    DEPENDS ${PROJECT_DEBUG}
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)

# Build AppImage.
set(UPDATE \"gh-releases-zsync|TKNgu|ng-ui|latest|NgUI.AppImage.zsync\")
add_custom_target(AppImage)
add_dependencies(AppImage ${PROJECT})
add_custom_command(TARGET AppImage
                     COMMAND ${CMAKE_COMMAND} -E
                         copy_directory ${CMAKE_SOURCE_DIR}/NgUI AppImage)
add_custom_command(TARGET AppImage
                     COMMAND ${CMAKE_COMMAND} -E
                         copy ${PROJECT} AppImage/bin/${PROJECT})
add_custom_command(TARGET AppImage
                     COMMAND ${CMAKE_COMMAND} -E
                         copy_directory ${CMAKE_SOURCE_DIR}/data AppImage/data)
add_custom_command(TARGET AppImage
                     COMMAND ${CMAKE_COMMAND} -E
                         copy_directory ${CMAKE_SOURCE_DIR}/lib AppImage/lib)
add_custom_command(TARGET AppImage
                     COMMAND ${CMAKE_SOURCE_DIR}/tool/appimagetool-x86_64.AppImage AppImage/ -u ${UPDATE})

# Run AppImage
add_custom_target(NgUI)
add_dependencies(NgUI AppImage)
add_custom_command(TARGET NgUI
                     COMMAND ./NgUI-x86_64.AppImage)