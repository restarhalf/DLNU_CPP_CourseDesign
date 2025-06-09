cmake_minimum_required(VERSION 3.25)
project("DLNU_CPP_CourseDesign")

set(CMAKE_CXX_STANDARD 20)

# 平台检测和配置
if(ANDROID)
    message(STATUS "Configuring for Android")
    find_package(SDL2 REQUIRED)
    find_package(SDL2_image REQUIRED)
    find_package(SDL2_ttf REQUIRED)
    find_package(SDL2_mixer REQUIRED)

    message(STATUS "Android SDL2_INCLUDE_DIR: ${SDL2_INCLUDE_DIR}")
    message(STATUS "Android SDL2_LIBRARY: ${SDL2_LIBRARY}")
    message(STATUS "Android SDL2_IMAGE_INCLUDE_DIR: ${SDL2_IMAGE_INCLUDE_DIR}")
    message(STATUS "Android SDL2_IMAGE_LIBRARY: ${SDL2_IMAGE_LIBRARY}")
    message(STATUS "Android SDL2_TTF_INCLUDE_DIR: ${SDL2_TTF_INCLUDE_DIR}")
    message(STATUS "Android SDL2_TTF_LIBRARY: ${SDL2_TTF_LIBRARY}")
    message(STATUS "Android SDL2_MIXER_INCLUDE_DIR: ${SDL2_MIXER_INCLUDE_DIR}")
    message(STATUS "Android SDL2_MIXER_LIBRARY: ${SDL2_MIXER_LIBRARY}")

elseif(APPLE)
    find_package(SDL2 REQUIRED)
    find_package(SDL2_image REQUIRED)
    find_package(SDL2_ttf REQUIRED)
    find_package(SDL2_mixer REQUIRED)

    message(STATUS "macOS SDL2_INCLUDE_DIR: ${SDL2_INCLUDE_DIR}")
    message(STATUS "macOS SDL2_LIBRARIES: ${SDL2_LIBRARIES}")
elseif(UNIX AND NOT APPLE AND NOT ANDROID)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(SDL2 REQUIRED sdl2)
    pkg_check_modules(SDL2_IMAGE REQUIRED SDL2_image)
    pkg_check_modules(SDL2_TTF REQUIRED SDL2_ttf)
    pkg_check_modules(SDL2_MIXER REQUIRED SDL2_mixer)

    # 打印调试信息
    message(STATUS "Linux SDL2 Include Dirs: ${SDL2_INCLUDE_DIRS}")
    message(STATUS "Linux SDL2 Libraries: ${SDL2_LIBRARIES}")
else()
    message(STATUS "Configuring for Windows (or default)")
endif()

add_executable(${PROJECT_NAME} main.cpp)

# 平台特定的包含目录和链接配置
if(ANDROID)
    target_include_directories(${PROJECT_NAME} PRIVATE
            ${SDL2_INCLUDE_DIR}
            ${SDL2_IMAGE_INCLUDE_DIR}
            ${SDL2_TTF_INCLUDE_DIR}
            ${SDL2_MIXER_INCLUDE_DIR}
            "${CMAKE_CURRENT_SOURCE_DIR}/api/lyt/include"
            "${CMAKE_CURRENT_SOURCE_DIR}/api/lx/include")
elseif(APPLE)
    target_include_directories(${PROJECT_NAME} PRIVATE
            ${SDL2_INCLUDE_DIR}
            ${SDL2_IMAGE_INCLUDE_DIR}
            ${SDL2_TTF_INCLUDE_DIR}
            ${SDL2_MIXER_INCLUDE_DIR}
            "${CMAKE_CURRENT_SOURCE_DIR}/api/lyt/include"
            "${CMAKE_CURRENT_SOURCE_DIR}/api/lx/include")
elseif(UNIX AND NOT APPLE AND NOT ANDROID)
    target_include_directories(${PROJECT_NAME} PRIVATE
            ${SDL2_INCLUDE_DIRS}
            ${SDL2_IMAGE_INCLUDE_DIRS}
            ${SDL2_TTF_INCLUDE_DIRS}
            ${SDL2_MIXER_INCLUDE_DIRS}
            "${CMAKE_CURRENT_SOURCE_DIR}/api/lyt/include"
            "${CMAKE_CURRENT_SOURCE_DIR}/api/lx/include")
else()
    target_include_directories(${PROJECT_NAME} PRIVATE
            "${CMAKE_CURRENT_SOURCE_DIR}/lib/dep/plugins/SDL2/include"
            "${CMAKE_CURRENT_SOURCE_DIR}/api/lyt/include"
            "${CMAKE_CURRENT_SOURCE_DIR}/api/lx/include")
    target_link_directories(${PROJECT_NAME} PRIVATE
            "${CMAKE_CURRENT_SOURCE_DIR}/lib/dep/plugins/SDL2/lib/x64")
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
        api/lx/src/ScoreManager.cpp)

if(ANDROID)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        SDL2::SDL2
        SDL2::SDL2main
        SDL2_image::SDL2_image
        SDL2_ttf::SDL2_ttf
        SDL2_mixer::SDL2_mixer

        log
        android
        EGL
        GLESv2
        OpenSLES
        )
elseif(APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        SDL2::SDL2
        SDL2::SDL2main
        SDL2_image::SDL2_image
        SDL2_ttf::SDL2_ttf
        SDL2_mixer::SDL2_mixer)
elseif(UNIX AND NOT APPLE AND NOT ANDROID)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        ${SDL2_LIBRARIES}
        ${SDL2_IMAGE_LIBRARIES}
        ${SDL2_TTF_LIBRARIES}
        ${SDL2_MIXER_LIBRARIES})
else()
    target_link_libraries(${PROJECT_NAME} PRIVATE
        SDL2
        SDL2main
        SDL2_image
        SDL2_ttf
        SDL2_mixer)
endif()

if(ANDROID)

get_filename_component(ASSET_DIR_ABS "${CMAKE_CURRENT_SOURCE_DIR}/asset" ABSOLUTE)
set_property(TARGET ${PROJECT_NAME} PROPERTY VS_ANDROID_ सोर्स_Դիր "${ASSET_DIR_ABS}")
SDL_SetHint(SDL_HINT_ANDROID_ASSETS_PATH, "./")
message(STATUS "Android assets directory should be: ${CMAKE_CURRENT_SOURCE_DIR}/asset")
endif()
