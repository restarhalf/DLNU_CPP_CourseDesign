cmake_minimum_required(VERSION 3.10)
project("DLNU_CPP_CourseDesign")

set(CMAKE_CXX_STANDARD 20)

# 显示诊断信息
message(STATUS "Building ${PROJECT_NAME} in ${CMAKE_BUILD_TYPE} mode")
message(STATUS "Current source dir: ${CMAKE_CURRENT_SOURCE_DIR}")

# 检查系统和环境
if(DEFINED ENV{CI} OR DEFINED ENV{GITHUB_ACTIONS})
    message(STATUS "Running in CI environment")
endif()

# 源文件列表
set(SOURCE_FILES
    main.cpp
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

# 头文件目录
set(INCLUDE_DIRS
    "${CMAKE_CURRENT_SOURCE_DIR}/api/lyt/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/api/lx/include"
)

# 添加可执行文件
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# 添加包含目录
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIRS})

# SDL2 库配置
# 1. 首先尝试使用系统的SDL2（通常由环境或包管理器提供）
find_package(SDL2 QUIET)
find_package(SDL2_image QUIET)
find_package(SDL2_ttf QUIET)
find_package(SDL2_mixer QUIET)

if(SDL2_FOUND AND SDL2_image_FOUND AND SDL2_ttf_FOUND AND SDL2_mixer_FOUND)
    message(STATUS "Using system SDL2 libraries")

    target_include_directories(${PROJECT_NAME} PRIVATE
        ${SDL2_INCLUDE_DIRS}
        ${SDL2_IMAGE_INCLUDE_DIRS}
        ${SDL2_TTF_INCLUDE_DIRS}
        ${SDL2_MIXER_INCLUDE_DIRS}
    )

    target_link_libraries(${PROJECT_NAME} PRIVATE
        ${SDL2_LIBRARIES}
        ${SDL2_IMAGE_LIBRARIES}
        ${SDL2_TTF_LIBRARIES}
        ${SDL2_MIXER_LIBRARIES}
    )
else()
    # 系统SDL2库未找到，使用项目自带的SDL2
    message(STATUS "System SDL2 not found, using bundled SDL2 libraries")

    # 检查项目是否包含SDL2
    set(SDL2_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib/dep/plugins/SDL2")

    if(NOT EXISTS "${SDL2_DIR}")
        message(FATAL_ERROR "SDL2 not found in ${SDL2_DIR}. Please install SDL2 or add it to the project.")
    endif()

    # 设置平台特定的库路径
    if(ANDROID)
        set(SDL2_INCLUDE_DIR "${SDL2_DIR}/android/include")
        set(SDL2_LIB_DIR "${SDL2_DIR}/android/libs/${ANDROID_ABI}")
        message(STATUS "Using Android SDL2: ${SDL2_LIB_DIR}")
    elseif(WIN32)
        set(SDL2_INCLUDE_DIR "${SDL2_DIR}/include")
        if(CMAKE_SIZEOF_VOID_P EQUAL 8)
            set(SDL2_LIB_DIR "${SDL2_DIR}/lib/x64")
            message(STATUS "Using Windows x64 SDL2: ${SDL2_LIB_DIR}")
        else()
            set(SDL2_LIB_DIR "${SDL2_DIR}/lib/x86")
            message(STATUS "Using Windows x86 SDL2: ${SDL2_LIB_DIR}")
        endif()
    else()
        # 其他平台（Linux, macOS等）
        set(SDL2_INCLUDE_DIR "${SDL2_DIR}/include")
        set(SDL2_LIB_DIR "${SDL2_DIR}/lib")
        message(STATUS "Using generic SDL2: ${SDL2_LIB_DIR}")
    endif()

    # 添加SDL2头文件目录
    if(EXISTS "${SDL2_INCLUDE_DIR}")
        target_include_directories(${PROJECT_NAME} PRIVATE "${SDL2_INCLUDE_DIR}")
    else()
        message(WARNING "SDL2 include directory not found: ${SDL2_INCLUDE_DIR}")
    endif()

    # 添加SDL2库目录
    if(EXISTS "${SDL2_LIB_DIR}")
        target_link_directories(${PROJECT_NAME} PRIVATE "${SDL2_LIB_DIR}")

        # 链接SDL2库
        target_link_libraries(${PROJECT_NAME} PRIVATE
            SDL2
            SDL2main
            SDL2_image
            SDL2_ttf
            SDL2_mixer
        )

        # Windows特殊处理：复制DLL到目标目录
        if(WIN32)
            # 检查DLL文件是否存在
            if(EXISTS "${SDL2_LIB_DIR}/SDL2.dll")
                add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy_if_different
                    "${SDL2_LIB_DIR}/SDL2.dll"
                    "${SDL2_LIB_DIR}/SDL2_image.dll"
                    "${SDL2_LIB_DIR}/SDL2_ttf.dll"
                    "${SDL2_LIB_DIR}/SDL2_mixer.dll"
                    $<TARGET_FILE_DIR:${PROJECT_NAME}>
                )
                message(STATUS "SDL2 DLLs will be copied to output directory")
            else()
                message(WARNING "SDL2 DLLs not found in ${SDL2_LIB_DIR}")
            endif()
        endif()
    else()
        message(WARNING "SDL2 library directory not found: ${SDL2_LIB_DIR}")
        message(STATUS "Building without SDL2, which may cause compilation errors")
    endif()
endif()

# 如果在Linux上，可能需要额外的库
if(UNIX AND NOT APPLE AND NOT ANDROID)
    find_package(Threads REQUIRED)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_THREAD_LIBS_INIT})
    target_link_libraries(${PROJECT_NAME} PRIVATE dl)
endif()

# Android特殊处理
if(ANDROID)
    find_library(LOG_LIB log)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${LOG_LIB})
endif()

message(STATUS "Configuration complete for ${PROJECT_NAME}")
