cmake_minimum_required(VERSION 3.29)
project("DLNU_CPP_CourseDesign")

set(CMAKE_CXX_STANDARD 20)

# 确保 CMake 能找到自定义模块
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

# 平台特定的 SDL2 查找逻辑
if(WIN32)
    # Windows 平台直接指定包含目录和库文件
    message(STATUS "Configure for Windows platform")

    # 检查 SDL2 目录是否存在
    set(SDL2_BASE "${CMAKE_SOURCE_DIR}/lib/dep/plugins/SDL2")
    if(EXISTS "${SDL2_BASE}")
        message(STATUS "Found SDL2 at ${SDL2_BASE}")
        # SDL2 包含目录
        set(SDL2_INCLUDE_DIRS "${SDL2_BASE}/include")
        # 设置架构目录
        if(CMAKE_SIZEOF_VOID_P EQUAL 8)
            set(SDL2_LIB_DIR "${SDL2_BASE}/lib/x64")
        else()
            set(SDL2_LIB_DIR "${SDL2_BASE}/lib/x86")
        endif()
    else()
        message(FATAL_ERROR "SDL2 directory not found at ${SDL2_BASE}")
    endif()
elseif(ANDROID)
    # Android 平台不使用 CMake 查找 SDL2，由 Gradle 负责
    message(STATUS "Android build - SDL2 will be handled by Gradle")
else()
    # 在 Linux/macOS，使用我们的自定义查找模块
    message(STATUS "Using system SDL2 with custom Find module")
endif()

# 所有平台都使用我们的自定义 FindSDL2 模块
find_package(SDL2 REQUIRED)

# 在 Linux/macOS 上使用系统的 SDL2 扩展库
if(NOT WIN32 AND NOT ANDROID)
    # 尝试使用系统的查找模块，若失败将使用缺省处理
    find_package(SDL2_image QUIET)
    find_package(SDL2_ttf QUIET)
    find_package(SDL2_mixer QUIET)

    # 如果找不到配置文件，使用 pkg-config
    if(NOT SDL2_image_FOUND)
        find_package(PkgConfig QUIET)
        if(PKG_CONFIG_FOUND)
            pkg_check_modules(SDL2_IMAGE QUIET SDL2_image)
        endif()
    endif()

    if(NOT SDL2_ttf_FOUND)
        find_package(PkgConfig QUIET)
        if(PKG_CONFIG_FOUND)
            pkg_check_modules(SDL2_TTF QUIET SDL2_ttf)
        endif()
    endif()

    if(NOT SDL2_mixer_FOUND)
        find_package(PkgConfig QUIET)
        if(PKG_CONFIG_FOUND)
            pkg_check_modules(SDL2_MIXER QUIET SDL2_mixer)
        endif()
    endif()
endif()

add_executable(${PROJECT_NAME} main.cpp)

# 包含目录设置
target_include_directories(${PROJECT_NAME} PRIVATE
    "${CMAKE_SOURCE_DIR}/api/lyt/include"
    "${CMAKE_SOURCE_DIR}/api/lx/include"
)

# Windows 平台额外包含 SDL2 目录
if(WIN32)
    target_include_directories(${PROJECT_NAME} PRIVATE
        "${SDL2_INCLUDE_DIRS}"
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
        "${SDL2_LIB_DIR}"
    )
    target_link_libraries(${PROJECT_NAME} PRIVATE
        SDL2 SDL2main SDL2_image SDL2_ttf SDL2_mixer
    )
elseif(NOT ANDROID)
    # Linux/macOS 使用导入目标
    target_link_libraries(${PROJECT_NAME} PRIVATE
        ${SDL2_LIBRARIES}
    )

    # 链接其他 SDL2 组件，如果找到的话
    if(SDL2_IMAGE_FOUND OR SDL2_image_FOUND)
        target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_IMAGE_LIBRARIES})
    endif()

    if(SDL2_TTF_FOUND OR SDL2_ttf_FOUND)
        target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_TTF_LIBRARIES})
    endif()

    if(SDL2_MIXER_FOUND OR SDL2_mixer_FOUND)
        target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_MIXER_LIBRARIES})
    endif()
endif()
