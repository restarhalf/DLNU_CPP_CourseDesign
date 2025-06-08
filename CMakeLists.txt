cmake_minimum_required(VERSION 3.29)
project("DLNU_CPP_CourseDesign")

set(CMAKE_CXX_STANDARD 20)

# 确保 CMake 能找到自定义模块
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

# 平台特定的 SDL2 查找逻辑
if(WIN32)
    # 对于 Windows，使用预设的目录查找 SDL2
    set(SDL2_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib/dep/plugins/SDL2/cmake" CACHE PATH "SDL2 config directory")
    set(SDL2_image_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib/dep/plugins/SDL2_image/cmake" CACHE PATH "SDL2_image config directory")
    set(SDL2_ttf_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib/dep/plugins/SDL2_ttf/cmake" CACHE PATH "SDL2_ttf config directory")
    set(SDL2_mixer_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib/dep/plugins/SDL2_mixer/cmake" CACHE PATH "SDL2_mixer config directory")

    # 直接使用手动导入的 SDL2 库
    message(STATUS "Using SDL2 from: ${SDL2_DIR}")
    include("${SDL2_DIR}/sdl2-config.cmake")
    include("${SDL2_image_DIR}/sdl2_image-config.cmake")
    include("${SDL2_ttf_DIR}/sdl2_ttf-config.cmake")
    include("${SDL2_mixer_DIR}/sdl2_mixer-config.cmake")
elseif(ANDROID)
    # Android 平台不使用 CMake 查找 SDL2，由 Gradle 负责
    message(STATUS "Android build - SDL2 will be handled by Gradle")
else()
    # 在 Linux/macOS，使用系统库
    find_package(SDL2 REQUIRED)
    find_package(SDL2_image REQUIRED)
    find_package(SDL2_ttf REQUIRED)
    find_package(SDL2_mixer REQUIRED)
endif()

add_executable(${PROJECT_NAME} main.cpp)

# 包含目录设置
target_include_directories(${PROJECT_NAME} PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/api/lyt/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/api/lx/include"
)

# Windows 平台额外包含 SDL2 目录
if(WIN32)
    target_include_directories(${PROJECT_NAME} PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/lib/dep/plugins/SDL2/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/lib/dep/plugins/SDL2_image/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/lib/dep/plugins/SDL2_ttf/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/lib/dep/plugins/SDL2_mixer/include"
    )
endif()

# 源文件
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

# 链接 SDL2 库
if(WIN32)
    # Windows 平台使用直接链接
    target_link_directories(${PROJECT_NAME} PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/lib/dep/plugins/SDL2/lib/x64"
        "${CMAKE_CURRENT_SOURCE_DIR}/lib/dep/plugins/SDL2_image/lib/x64"
        "${CMAKE_CURRENT_SOURCE_DIR}/lib/dep/plugins/SDL2_ttf/lib/x64"
        "${CMAKE_CURRENT_SOURCE_DIR}/lib/dep/plugins/SDL2_mixer/lib/x64"
    )
    target_link_libraries(${PROJECT_NAME} PRIVATE
        SDL2 SDL2main SDL2_image SDL2_ttf SDL2_mixer
    )
elseif(NOT ANDROID)
    # Linux/macOS 使用导入目标
    target_link_libraries(${PROJECT_NAME} PRIVATE
        SDL2::SDL2 SDL2::SDL2main
        SDL2_image::SDL2_image
        SDL2_ttf::SDL2_ttf
        SDL2_mixer::SDL2_mixer
    )
endif()
