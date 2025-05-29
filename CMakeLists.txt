cmake_minimum_required(VERSION 3.29)
project("DLNU_CPP_CourseDesign")

set(CMAKE_CXX_STANDARD 20)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/SDL2/include")
link_directories("${CMAKE_CURRENT_SOURCE_DIR}/SDL2/lib/x64")

add_executable(DLNU_CPP_CourseDesign main.cpp
        game.cpp
        game.h
        Controller.cpp
        Controller.h
        Text.cpp
        Text.h
        Window.cpp
        Window.h
        Renderer.cpp
        Renderer.h
        ServerSide.cpp
)
target_link_libraries(DLNU_CPP_CourseDesign 
    SDL2
    SDL2main
    SDL2_image
    SDL2_ttf
    SDL2_mixer
)