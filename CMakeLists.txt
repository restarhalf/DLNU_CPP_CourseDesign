cmake_minimum_required(VERSION 3.29)
project("DLNU_CPP_CourseDesign")

set(CMAKE_CXX_STANDARD 20)

# 设置SDL2库路径（跨平台支持）
if(ANDROID)
    # Android平台SDL2配置
    set(SDL2_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib/dep/plugins/SDL2/android")
    include_directories(${SDL2_DIR}/include)
elseif(WIN32)
    # Windows平台SDL2配置
    set(SDL2_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib/dep/plugins/SDL2")

    # 根据编译架构选择对应的库路径
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        # 64位系统
        set(SDL2_LIB_DIR "${SDL2_DIR}/lib/x64")
    else()
        # 32位系统
        set(SDL2_LIB_DIR "${SDL2_DIR}/lib/x86")
    endif()
else()
    # 其他平台SDL2配置
    set(SDL2_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib/dep/plugins/SDL2")
    set(SDL2_LIB_DIR "${SDL2_DIR}/lib")
endif()

# 添加可执行文件
add_executable(${PROJECT_NAME} main.cpp)

# 添加包含目录
target_include_directories(${PROJECT_NAME} PRIVATE
        "${SDL2_DIR}/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/api/lyt/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/api/lx/include")

# 添加链接目录
if(NOT ANDROID)  # Android使用不同的链接方法
    target_link_directories(${PROJECT_NAME} PRIVATE
            "${SDL2_LIB_DIR}")
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
    find_library(SDL2 SDL2 REQUIRED PATHS "${SDL2_DIR}/libs/${ANDROID_ABI}")
    find_library(SDL2_image SDL2_image REQUIRED PATHS "${SDL2_DIR}/libs/${ANDROID_ABI}")
    find_library(SDL2_ttf SDL2_ttf REQUIRED PATHS "${SDL2_DIR}/libs/${ANDROID_ABI}")
    find_library(SDL2_mixer SDL2_mixer REQUIRED PATHS "${SDL2_DIR}/libs/${ANDROID_ABI}")

    target_link_libraries(${PROJECT_NAME} PRIVATE
            ${SDL2}
            ${SDL2_image}
            ${SDL2_ttf}
            ${SDL2_mixer}
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
if(WIN32 AND NOT CMAKE_BUILD_TYPE MATCHES "Release")
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SDL2_LIB_DIR}/SDL2.dll"
            "${SDL2_LIB_DIR}/SDL2_image.dll"
            "${SDL2_LIB_DIR}/SDL2_ttf.dll"
            "${SDL2_LIB_DIR}/SDL2_mixer.dll"
            $<TARGET_FILE_DIR:${PROJECT_NAME}>)
endif()
