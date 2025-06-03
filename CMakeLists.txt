cmake_minimum_required(VERSION 3.29)
project("DLNU_CPP_CourseDesign")

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME} main.cpp
        api/lx/src/AIFish.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/lib/dep/plugins/SDL2/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/api/lyt/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/api/lx/include")
target_link_directories(${PROJECT_NAME} PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/lib/dep/plugins/SDL2/lib/x64")

target_sources(${PROJECT_NAME} PRIVATE
        api/lyt/src/Button.cpp
        api/lyt/src/Game.cpp
        api/lyt/src/Image.cpp
        api/lyt/src/Text.cpp
        api/lyt/src/Window.cpp
        api/lyt/src/Music.cpp
        api/lyt/src/Renderer.cpp
        api/lyt/src/Controller.cpp
        api/lx/src/Fish.cpp
        api/lx/src/PlayerFish.cpp
        api/lx/src/AIFish.cpp
        api/lx/src/ScoreManager.cpp
)

target_link_libraries(DLNU_CPP_CourseDesign PRIVATE
        SDL2
        SDL2main
        SDL2_image
        SDL2_ttf
        SDL2_mixer
)
