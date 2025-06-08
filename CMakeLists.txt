cmake_minimum_required(VERSION 3.21)
project("DLNU_CPP_CourseDesign")

set(CMAKE_CXX_STANDARD 20)

# Android平台配置
if(ANDROID)
    message(STATUS "Configuring for Android platform...")

    if(NOT DEFINED ENV{ANDROID_NDK})
        message(FATAL_ERROR "ANDROID_NDK environment variable not set!")
    endif()

    # 设置Android特定选项
    set(CMAKE_ANDROID_ARCH_ABI "arm64-v8a")
    set(CMAKE_ANDROID_STL_TYPE "c++_static")
    set(CMAKE_ANDROID_API 26)

    message(STATUS "Android NDK path: $ENV{ANDROID_NDK}")
    message(STATUS "Android ABI: ${CMAKE_ANDROID_ARCH_ABI}")
    message(STATUS "Android API: ${CMAKE_ANDROID_API}")

    # 检查预编译的SDL2库
    set(SDL2_PATH "${CMAKE_CURRENT_SOURCE_DIR}/android/SDL2")
    set(SDL2_IMAGE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/android/SDL2_image")
    set(SDL2_TTF_PATH "${CMAKE_CURRENT_SOURCE_DIR}/android/SDL2_ttf")
    set(SDL2_MIXER_PATH "${CMAKE_CURRENT_SOURCE_DIR}/android/SDL2_mixer")

    # 如果预编译库不存在，则使用FetchContent下载
    if(NOT EXISTS "${SDL2_PATH}")
        include(FetchContent)
        set(FETCHCONTENT_QUIET OFF)

        message(STATUS "Downloading SDL2 dependencies...")

        FetchContent_Declare(
            SDL2
            GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
            GIT_TAG release-2.28.5
            GIT_PROGRESS TRUE
            GIT_SHALLOW TRUE
        )

        FetchContent_Declare(
            SDL2_image
            GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
            GIT_TAG release-2.8.2
            GIT_PROGRESS TRUE
            GIT_SHALLOW TRUE
        )

        FetchContent_Declare(
            SDL2_ttf
            GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
            GIT_TAG release-2.20.2
            GIT_PROGRESS TRUE
            GIT_SHALLOW TRUE
        )

        FetchContent_Declare(
            SDL2_mixer
            GIT_REPOSITORY https://github.com/libsdl-org/SDL_mixer.git
            GIT_TAG release-2.8.0
            GIT_PROGRESS TRUE
            GIT_SHALLOW TRUE
        )

        # 逐个下载和配置依赖
        foreach(dep IN ITEMS SDL2 SDL2_image SDL2_ttf SDL2_mixer)
            message(STATUS "Fetching ${dep}...")

            FetchContent_GetProperties(${dep})
            if(NOT ${dep}_POPULATED)
                FetchContent_Populate(${dep})

                if(EXISTS "${${dep}_SOURCE_DIR}")
                    message(STATUS "${dep} downloaded to: ${${dep}_SOURCE_DIR}")

                    if(${dep} STREQUAL "SDL2")
                        set(SDL_STATIC ON CACHE BOOL "Build static SDL2 library" FORCE)
                        set(SDL_SHARED OFF CACHE BOOL "Build shared SDL2 library" FORCE)
                        set(SDL_TEST OFF CACHE BOOL "Build SDL2 test programs" FORCE)
                    endif()

                    add_subdirectory(${${dep}_SOURCE_DIR} ${${dep}_BINARY_DIR})
                else()
                    message(FATAL_ERROR "${dep} download failed! Directory not found: ${${dep}_SOURCE_DIR}")
                endif()
            endif()
        endforeach()
    else()
        message(STATUS "Using pre-built SDL2 libraries from android directory")
    endif()
endif()

add_executable(${PROJECT_NAME} main.cpp)

# 平台特定的包含目录和链接配置
if(ANDROID)
    target_include_directories(${PROJECT_NAME} PRIVATE
            "${SDL2_SOURCE_DIR}/include"
            "${SDL2_image_SOURCE_DIR}/include"
            "${SDL2_ttf_SOURCE_DIR}/include"
            "${SDL2_mixer_SOURCE_DIR}/include"
            "${CMAKE_CURRENT_SOURCE_DIR}/api/lyt/include"
            "${CMAKE_CURRENT_SOURCE_DIR}/api/lx/include")

    # 确保静态链接
    set_target_properties(${PROJECT_NAME} PROPERTIES
        LINK_FLAGS "-static-libstdc++"
    )
elseif(APPLE)
    target_include_directories(${PROJECT_NAME} PRIVATE
            ${SDL2_INCLUDE_DIRS}
            ${SDL2_IMAGE_INCLUDE_DIRS}
            ${SDL2_TTF_INCLUDE_DIRS}
            ${SDL2_MIXER_INCLUDE_DIRS}
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
if(ANDROID)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        SDL2::SDL2-static
        SDL2_image::SDL2_image-static
        SDL2_ttf::SDL2_ttf-static
        SDL2_mixer::SDL2_mixer-static)
elseif(APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        SDL2::SDL2
        SDL2::SDL2main
        SDL2_image::SDL2_image
        SDL2_ttf::SDL2_ttf
        SDL2_mixer::SDL2_mixer)
else()
    target_link_libraries(${PROJECT_NAME} PRIVATE
        SDL2
        SDL2main
        SDL2_image
        SDL2_ttf
        SDL2_mixer)
endif()
