# Cmake version
cmake_minimum_required(VERSION 3.0)

# CFLAG
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(LINK_FLAG dl pthread X11 Xrandr Xinerama Xxf86vm Xcursor glfw)
set(PROJECT ng-ui)
set(PROJECT_DEBUG debug)

# Include header
include_directories(include)
include_directories(local/include)
link_directories(${CMAKE_SOURCE_DIR}/local/lib)

#For the static library:
file(GLOB SOURCES "src/*.cpp" "src/*.c")

# Project
project(${PROJECT})
add_executable(${PROJECT} ${SOURCES})
target_link_libraries(${PROJECT} ${LINK_FLAG})

# Debug
project(${PROJECT_DEBUG})
add_executable(${PROJECT_DEBUG} ${SOURCES})
target_link_libraries(${PROJECT_DEBUG} ${LINK_FLAG})

# Run Debug
target_compile_definitions(${PROJECT_DEBUG} PUBLIC DEBUG_MEMORY)
add_custom_target(run
    COMMAND ${PROJECT_DEBUG} ".."
    DEPENDS ${PROJECT_DEBUG}
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)

# Build NgUI.AppImage.
set(UPDATE \"gh-releases-zsync|TKNgu|ng-ui|latest|NgUI-x86_64.AppImage.zsync\")
add_custom_target(NgUI.AppImage)
add_dependencies(NgUI.AppImage ${PROJECT})
add_custom_command(TARGET NgUI.AppImage
                     COMMAND ${CMAKE_COMMAND} -E
                         make_directory NgUI)
add_custom_command(TARGET NgUI.AppImage
                     COMMAND ${CMAKE_COMMAND} -E
                         copy_directory ${CMAKE_SOURCE_DIR}/NgUI NgUI)
add_custom_command(TARGET NgUI.AppImage
                     COMMAND ${CMAKE_COMMAND} -E
                         copy ${PROJECT} NgUI/bin/${PROJECT})
add_custom_command(TARGET NgUI.AppImage
                     COMMAND ${CMAKE_COMMAND} -E
                         copy_directory ${CMAKE_SOURCE_DIR}/data NgUI/data)
add_custom_command(TARGET NgUI.AppImage
                     COMMAND ${CMAKE_COMMAND} -E
                         copy_directory ${CMAKE_SOURCE_DIR}/local/lib NgUI/lib)
add_custom_command(TARGET NgUI.AppImage
                     COMMAND ${CMAKE_SOURCE_DIR}/local/bin/appimagetool-x86_64.AppImage NgUI -u ${UPDATE})

# Run NgUI.AppImage
add_custom_target(NgUI)
add_dependencies(NgUI NgUI.AppImage)
add_custom_command(TARGET NgUI
                     COMMAND ./NgUI-x86_64.AppImage)

add_custom_target(release)
add_dependencies(release NgUI.AppImage)