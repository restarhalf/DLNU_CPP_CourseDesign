cmake_minimum_required(VERSION 3.25)  # 降低最低版本要求，以适应CI环境
project("DLNU_CPP_CourseDesign")

set(CMAKE_CXX_STANDARD 20)

# 平台检测和配置
if(ANDROID)
    message(STATUS "Configuring for Android")
    # 对于安卓，find_package 需要 CMAKE_PREFIX_PATH 指向预编译的 SDL2 库
    # 或者在 CI 中编译 SDL2 并设置此路径。
    # SDL2 的 CMake 脚本通常会创建导入目标 (SDL2::SDL2 等)。
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

# macOS 平台配置
elseif(APPLE)
    # 设置 SDL2 查找路径 (Homebrew)
    # 对于 find_package 使用导入目标 (SDL2::SDL2)，通常不需要手动设置这些 DIR 变量
    # 但如果 find_package 找不到，可以取消注释并调整下面的 CMAKE_PREFIX_PATH 或 CMAKE_MODULE_PATH
    # set(SDL2_DIR ${HOMEBREW_PREFIX}/lib/cmake/SDL2) # 等

    find_package(SDL2 REQUIRED)
    find_package(SDL2_image REQUIRED)
    find_package(SDL2_ttf REQUIRED)
    find_package(SDL2_mixer REQUIRED)

    # 使用由 find_package 设置的标准变量或导入目标
    message(STATUS "macOS SDL2_INCLUDE_DIR: ${SDL2_INCLUDE_DIR}")
    message(STATUS "macOS SDL2_LIBRARIES: ${SDL2_LIBRARIES}")
# Linux 平台配置
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
    # 如果SDL的CMake脚本不自动处理，可能需要手动添加：
    # get_filename_component(ASSET_DIR_ABS "${CMAKE_CURRENT_SOURCE_DIR}/asset" ABSOLUTE)
    # set_property(TARGET ${PROJECT_NAME} PROPERTY VS_ANDROID_ सोर्स_Դիր "${ASSET_DIR_ABS}")
    # 或者通过 SDL_SetHint(SDL_HINT_ANDROID_ASSETS_PATH, "./");
    # SDL2 v2.0.14+ 应该会自动处理项目根目录下的 assets 文件夹
    # message(STATUS "Android assets directory should be: ${CMAKE_CURRENT_SOURCE_DIR}/asset")
endif()
