cmake_minimum_required(VERSION 3.29)
project("DLNU_CPP_CourseDesign")

set(CMAKE_CXX_STANDARD 20)

# On Unix/Mac use find_package for SDL2 and components
if(NOT WIN32)
    find_package(SDL2 REQUIRED)
    find_package(SDL2_image REQUIRED)
    find_package(SDL2_ttf REQUIRED)
    find_package(SDL2_mixer REQUIRED)
endif()

add_executable(${PROJECT_NAME} main.cpp)

# Include directories
if(WIN32)
    # Windows: use local SDL2 include
    target_include_directories(${PROJECT_NAME} PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/lib/dep/plugins/SDL2/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/api/lyt/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/api/lx/include"
    )
    # Find SDL2 on Windows
    find_package(SDL2 REQUIRED PATHS "${CMAKE_CURRENT_SOURCE_DIR}/lib/dep/plugins/SDL2/cmake")
    find_package(SDL2_image REQUIRED PATHS "${CMAKE_CURRENT_SOURCE_DIR}/lib/dep/plugins/SDL2_image/cmake")
    find_package(SDL2_ttf REQUIRED PATHS "${CMAKE_CURRENT_SOURCE_DIR}/lib/dep/plugins/SDL2_ttf/cmake")
    find_package(SDL2_mixer REQUIRED PATHS "${CMAKE_CURRENT_SOURCE_DIR}/lib/dep/plugins/SDL2_mixer/cmake")
else()
    # Unix/Mac: find and use system SDL2
    find_package(SDL2 REQUIRED)
    find_package(SDL2_image REQUIRED)
    find_package(SDL2_ttf REQUIRED)
    find_package(SDL2_mixer REQUIRED)
    target_include_directories(${PROJECT_NAME} PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/api/lyt/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/api/lx/include"
    )
endif()

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

# Link SDL2 conditionally: use local libs on Windows, imported targets on Unix/Mac
if(WIN32)
    target_link_directories(${PROJECT_NAME} PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/lib/dep/plugins/SDL2/lib/x64"
    )
    target_link_libraries(${PROJECT_NAME} PRIVATE
        SDL2
        SDL2main
        SDL2_image
        SDL2_ttf
        SDL2_mixer
    )
else()
    target_link_libraries(${PROJECT_NAME} PRIVATE
        SDL2::SDL2
        SDL2::SDL2main
        SDL2_image::SDL2_image
        SDL2_ttf::SDL2_ttf
        SDL2_mixer::SDL2_mixer
    )
endif()
