cmake_minimum_required(VERSION 3.29)
project("DLNU_CPP_CourseDesign")

set(CMAKE_CXX_STANDARD 20)

# 检测操作系统类型
if(ANDROID OR APPLE)
    include(FetchContent)
    # SDL2
    FetchContent_Declare(
        SDL2
        URL https://github.com/libsdl-org/SDL/releases/download/release-2.28.5/SDL2-2.28.5.tar.gz
        URL_HASH SHA256=332cb37d0be20cb9541739c61f79bae5a477427d79ae85e352089afdaf6666e4
    )

    # SDL2_image
    FetchContent_Declare(
        SDL2_image
        URL https://github.com/libsdl-org/SDL_image/releases/download/release-2.8.2/SDL2_image-2.8.2.tar.gz
        URL_HASH SHA256=8f486bbfbcf8464dd58c9e5d93394ab0255ce68b51c5a966a918244820a76ddc
    )

    # SDL2_ttf
    FetchContent_Declare(
        SDL2_ttf
        URL https://github.com/libsdl-org/SDL_ttf/releases/download/release-2.20.2/SDL2_ttf-2.20.2.tar.gz
        URL_HASH SHA256=9dc71ed93487521c207617c0d340c45515b5b23f171e1d20bd7367b561f4a843
    )

    # SDL2_mixer
    FetchContent_Declare(
        SDL2_mixer
        URL https://github.com/libsdl-org/SDL_mixer/releases/download/release-2.8.0/SDL2_mixer-2.8.0.tar.gz
        URL_HASH SHA256=1cfb39a55ea1fc0d38bc7d0fe57b8e5a59783091f0fb1a8def3531875d6a7f3e
    )

    # 下载并构建所有依赖
    FetchContent_MakeAvailable(SDL2 SDL2_image SDL2_ttf SDL2_mixer)
endif()

add_executable(${PROJECT_NAME} main.cpp)

# 平台特定的包含目录和链接配置
if(ANDROID OR APPLE)
    target_include_directories(${PROJECT_NAME} PRIVATE
            "${SDL2_SOURCE_DIR}/include"
            "${SDL2_image_SOURCE_DIR}/include"
            "${SDL2_ttf_SOURCE_DIR}/include"
            "${SDL2_mixer_SOURCE_DIR}/include"
            "${CMAKE_CURRENT_SOURCE_DIR}/api/lyt/include"
            "${CMAKE_CURRENT_SOURCE_DIR}/api/lx/include")
else()
    # Windows和其他平台使用原有配置
    target_include_directories(${PROJECT_NAME} PRIVATE
            "${CMAKE_CURRENT_SOURCE_DIR}/lib/dep/plugins/SDL2/include"
            "${CMAKE_CURRENT_SOURCE_DIR}/api/lyt/include"
            "${CMAKE_CURRENT_SOURCE_DIR}/api/lx/include")
    target_link_directories(${PROJECT_NAME} PRIVATE
            "${CMAKE_CURRENT_SOURCE_DIR}/lib/dep/plugins/SDL2/lib/x64")
endif()

# 添加源文件
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

# 链接SDL2库
if(ANDROID OR APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        SDL2::SDL2
        SDL2::SDL2main
        SDL2_image::SDL2_image
        SDL2_ttf::SDL2_ttf
        SDL2_mixer::SDL2_mixer)
else()
    target_link_libraries(${PROJECT_NAME} PRIVATE SDL2 SDL2main SDL2_image SDL2_ttf SDL2_mixer)
endif()
