cmake_minimum_required(VERSION 3.21)
project("DLNU_CPP_CourseDesign")

set(CMAKE_CXX_STANDARD 20)

# macOS 平台配置
if(APPLE)
    # 设置 SDL2 查找路径
    set(SDL2_DIR ${HOMEBREW_PREFIX}/lib/cmake/SDL2)
    set(SDL2_IMAGE_DIR ${HOMEBREW_PREFIX}/lib/cmake/SDL2_image)
    set(SDL2_TTF_DIR ${HOMEBREW_PREFIX}/lib/cmake/SDL2_ttf)
    set(SDL2_MIXER_DIR ${HOMEBREW_PREFIX}/lib/cmake/SDL2_mixer)

    # 查找所有 SDL2 相关包
    find_package(SDL2 REQUIRED)
    find_package(SDL2_image REQUIRED)
    find_package(SDL2_ttf REQUIRED)
    find_package(SDL2_mixer REQUIRED)

    message(STATUS "SDL2_INCLUDE_DIRS: ${SDL2_INCLUDE_DIRS}")
    message(STATUS "SDL2_LIBRARIES: ${SDL2_LIBRARIES}")
endif()

# Android平台配置
if(ANDROID)
    include(FetchContent)

    # 设置FetchContent全局属性
    set(FETCHCONTENT_TRY_FIND_PACKAGE_MODE NEVER)
    set(FETCHCONTENT_QUIET OFF)
    set(FETCHCONTENT_FULLY_DISCONNECTED OFF)

    message(STATUS "Configuring SDL2 dependencies for Android...")

    # 设置Android特定选项
    set(SDL_SHARED OFF CACHE BOOL "Build a shared version of the library")
    set(SDL_STATIC ON CACHE BOOL "Build a static version of the library")
    set(SDL2_DISABLE_INSTALL ON)
    set(SDL2IMAGE_INSTALL OFF)
    set(SDL2TTF_INSTALL OFF)
    set(SDL2MIXER_INSTALL OFF)

    # SDL2核心库
    FetchContent_Declare(
        SDL2
        URL https://github.com/libsdl-org/SDL/releases/download/release-2.28.5/SDL2-2.28.5.tar.gz
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    )

    # SDL2_image
    FetchContent_Declare(
        SDL2_image
        URL https://github.com/libsdl-org/SDL_image/releases/download/release-2.8.2/SDL2_image-2.8.2.tar.gz
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    )

    # SDL2_ttf
    FetchContent_Declare(
        SDL2_ttf
        URL https://github.com/libsdl-org/SDL_ttf/releases/download/release-2.20.2/SDL2_ttf-2.20.2.tar.gz
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    )

    # SDL2_mixer
    FetchContent_Declare(
        SDL2_mixer
        URL https://github.com/libsdl-org/SDL_mixer/releases/download/release-2.8.0/SDL2_mixer-2.8.0.tar.gz
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    )

    # Android特定配置
    set(CMAKE_ANDROID_ARCH_ABI "arm64-v8a")
    set(CMAKE_ANDROID_STL_TYPE "c++_static")
    set(CMAKE_ANDROID_API 26)

    # 下载并构建所有依赖，分开处理以便于错误排查
    foreach(dep IN ITEMS SDL2 SDL2_image SDL2_ttf SDL2_mixer)
        # SDL2特定配置
        # 这些设置需要在 SDL2 的 CMakeLists.txt 文件通过 add_subdirectory 处理之前进行。
        # FetchContent_MakeAvailable 会在内部调用 add_subdirectory。
        # 因此，在调用 FetchContent_MakeAvailable 之前设置这些变量。
        if(${dep} STREQUAL "SDL2")
            set(SDL_STATIC ON CACHE BOOL "Build static SDL2 library" FORCE)
            set(SDL_SHARED OFF CACHE BOOL "Build shared SDL2 library" FORCE)
        endif()

        # SDL2_ttf 特定配置：使用 vendored Freetype
        if(${dep} STREQUAL "SDL2_ttf")
            set(SDL2TTF_VENDORED ON CACHE BOOL "Use vendored dependencies for SDL2_ttf" FORCE)
        endif()

        # SDL2_mixer 特定配置：使用 vendored 依赖 (特别是 Ogg)
        if(${dep} STREQUAL "SDL2_mixer")
            set(SDL2MIXER_VENDORED ON CACHE BOOL "Use vendored dependencies for SDL2_mixer" FORCE)
            set(SDL2MIXER_OGG_VENDORED ON CACHE BOOL "Use vendored Ogg for SDL2_mixer" FORCE)
            # SDL2MIXER_VENDORED ON 通常会处理其他格式，但为了明确，特别是针对 Ogg 错误
        endif()

        FetchContent_MakeAvailable(${dep}) # 此命令声明、填充（如果需要）并使目标可用。

        # 可选：检查并显示状态
        FetchContent_GetProperties(${dep}) # 获取更新后的属性，如 _SOURCE_DIR
        if(${dep}_POPULATED)
            message(STATUS "${dep} is available. Source: ${${dep}_SOURCE_DIR}")
        else()
            # 如果 FetchContent_MakeAvailable 失败，它通常会直接报错。
            message(WARNING "Could not make ${dep} available. Check logs for details.")
        endif()
    endforeach()

    # 验证所有依赖是否都已正确配置
    foreach(dep IN ITEMS SDL2 SDL2_image SDL2_ttf SDL2_mixer)
        if(NOT TARGET ${dep}::${dep})
            message(FATAL_ERROR "${dep} target not found after configuration")
        endif()
    endforeach()

    message(STATUS "All SDL2 dependencies configured successfully")
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
