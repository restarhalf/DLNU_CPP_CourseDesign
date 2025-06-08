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

    message(STATUS "Configuring SDL2 dependencies for Android...")

    # SDL2核心库
    FetchContent_Declare(
        SDL2
        URL https://github.com/libsdl-org/SDL/releases/download/release-2.28.5/SDL2-2.28.5.tar.gz
        URL_HASH SHA256=d91b4457ba25b8a27971746af57a24a949c146e54687b03611e496538b137e5f
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
        DOWNLOAD_RETRIES 3
    )

    # SDL2_image
    FetchContent_Declare(
        SDL2_image
        URL https://github.com/libsdl-org/SDL_image/releases/download/release-2.8.2/SDL2_image-2.8.2.tar.gz
        URL_HASH SHA256=76f3725fe79e901729e07948d693599dd5bdd38f783aebd8e38a19ac0825bc18
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
        DOWNLOAD_RETRIES 3
    )

    # SDL2_ttf
    FetchContent_Declare(
        SDL2_ttf
        URL https://github.com/libsdl-org/SDL_ttf/releases/download/release-2.20.2/SDL2_ttf-2.20.2.tar.gz
        URL_HASH SHA256=9dc71ed93487521b107a2c4a9ca6bf43fb62f6bddd5c26b055e6b91418a22053
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
        DOWNLOAD_RETRIES 3
    )

    # SDL2_mixer
    FetchContent_Declare(
        SDL2_mixer
        URL https://github.com/libsdl-org/SDL_mixer/releases/download/release-2.8.0/SDL2_mixer-2.8.0.tar.gz
        URL_HASH SHA256=1cfb39a55ea1fc0d38bc7d0fe57b8e5a59783091f0fb1a8def3531875d6a7f3e
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
        DOWNLOAD_RETRIES 3
    )

    # Android特定配置
    set(CMAKE_ANDROID_ARCH_ABI "arm64-v8a")
    set(CMAKE_ANDROID_STL_TYPE "c++_static")

    # 下载并构建所有依赖，分开处理以便于错误排查
    foreach(dep IN ITEMS SDL2 SDL2_image SDL2_ttf SDL2_mixer)
        FetchContent_GetProperties(${dep})
        if(NOT ${dep}_POPULATED)
            message(STATUS "Fetching ${dep}...")
            FetchContent_Populate(${dep})

            # 检查下载是否成功
            if(NOT EXISTS "${${dep}_SOURCE_DIR}")
                message(FATAL_ERROR "Failed to fetch ${dep}. Source directory not found: ${${dep}_SOURCE_DIR}")
            endif()

            # 添加子目录
            add_subdirectory(${${dep}_SOURCE_DIR} ${${dep}_BINARY_DIR})
            message(STATUS "${dep} configured successfully")
        endif()
    endforeach()

    # 验证所有依赖是否都已正确配置
    if(NOT SDL2_POPULATED OR NOT SDL2_image_POPULATED OR NOT SDL2_ttf_POPULATED OR NOT SDL2_mixer_POPULATED)
        message(FATAL_ERROR "One or more SDL2 dependencies failed to configure properly")
    endif()

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
        SDL2::SDL2
        SDL2::SDL2main
        SDL2_image::SDL2_image
        SDL2_ttf::SDL2_ttf
        SDL2_mixer::SDL2_mixer)
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
