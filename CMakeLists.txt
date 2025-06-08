cmake_minimum_required(VERSION 3.29)
project("DLNU_CPP_CourseDesign")

set(CMAKE_CXX_STANDARD 20)

# 清除之前的缓存（解决GitHub Actions路径不一致问题）
if(DEFINED ENV{CI} OR DEFINED ENV{GITHUB_ACTIONS})
    # 如果在CI环境中，移除CMakeCache.txt以避免路径问题
    file(REMOVE "${CMAKE_BINARY_DIR}/CMakeCache.txt")
endif()

# 设置SDL2库路径（跨平台支持）
if(ANDROID)
    # Android平台SDL2配置
    set(SDL2_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib/dep/plugins/SDL2/android")
else()
    # 其他平台SDL2配置
    set(SDL2_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib/dep/plugins/SDL2")
endif()

# 根据平台和架构确定库目录
if(ANDROID)
    # 针对不同的Android ABI，库路径会有所不同
    set(SDL2_LIB_DIR "${SDL2_DIR}/libs/${ANDROID_ABI}")
    set(SDL2_INCLUDE_DIR "${SDL2_DIR}/include")
elseif(WIN32)
    # Windows平台根据架构选择库目录
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        # 64位系统
        set(SDL2_LIB_DIR "${SDL2_DIR}/lib/x64")
    else()
        # 32位系统
        set(SDL2_LIB_DIR "${SDL2_DIR}/lib/x86")
    endif()
    set(SDL2_INCLUDE_DIR "${SDL2_DIR}/include")
else()
    # 默认库路径（Linux、macOS等）
    set(SDL2_LIB_DIR "${SDL2_DIR}/lib")
    set(SDL2_INCLUDE_DIR "${SDL2_DIR}/include")
endif()

# 添加可执行文件
add_executable(${PROJECT_NAME} main.cpp)

# 添加包含目录
target_include_directories(${PROJECT_NAME} PRIVATE
        ${SDL2_INCLUDE_DIR}
        "${CMAKE_CURRENT_SOURCE_DIR}/api/lyt/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/api/lx/include")

# 添加链接目录
if(NOT ANDROID)  # Android使用不同的链接方法
    target_link_directories(${PROJECT_NAME} PRIVATE
            ${SDL2_LIB_DIR})
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
        api/lx/src/ScoreManager.cpp
)

# 链接SDL2库
if(ANDROID)
    # Android平台链接SDL2
    find_library(SDL2_LIB SDL2 REQUIRED PATHS ${SDL2_LIB_DIR})
    find_library(SDL2_IMAGE_LIB SDL2_image REQUIRED PATHS ${SDL2_LIB_DIR})
    find_library(SDL2_TTF_LIB SDL2_ttf REQUIRED PATHS ${SDL2_LIB_DIR})
    find_library(SDL2_MIXER_LIB SDL2_mixer REQUIRED PATHS ${SDL2_LIB_DIR})

    target_link_libraries(${PROJECT_NAME} PRIVATE
            ${SDL2_LIB}
            ${SDL2_IMAGE_LIB}
            ${SDL2_TTF_LIB}
            ${SDL2_MIXER_LIB}
            log)  # Android日志库
else()
    # Windows和其他平台链接SDL2
    target_link_libraries(${PROJECT_NAME} PRIVATE
            SDL2
            SDL2main
            SDL2_image
            SDL2_ttf
            SDL2_mixer)
endif()

# 复制SDL2 DLL到输出目录 (仅Windows)
if(WIN32)
    if(EXISTS "${SDL2_LIB_DIR}/SDL2.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${SDL2_LIB_DIR}/SDL2.dll"
                "${SDL2_LIB_DIR}/SDL2_image.dll"
                "${SDL2_LIB_DIR}/SDL2_ttf.dll"
                "${SDL2_LIB_DIR}/SDL2_mixer.dll"
                $<TARGET_FILE_DIR:${PROJECT_NAME}>)
    endif()
endif()

# 为GitHub Actions环境提供调试信息
if(DEFINED ENV{CI} OR DEFINED ENV{GITHUB_ACTIONS})
    message(STATUS "Running in CI environment")
    message(STATUS "Current source dir: ${CMAKE_CURRENT_SOURCE_DIR}")
    message(STATUS "SDL2_DIR: ${SDL2_DIR}")
    message(STATUS "SDL2_LIB_DIR: ${SDL2_LIB_DIR}")
    message(STATUS "SDL2_INCLUDE_DIR: ${SDL2_INCLUDE_DIR}")
endif()
