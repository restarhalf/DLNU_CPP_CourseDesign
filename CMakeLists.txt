cmake_minimum_required(VERSION 3.29)
project("DLNU_CPP_CourseDesign")

set(CMAKE_CXX_STANDARD 20)

# 添加自定义模块路径
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

# 使用自定义 FindSDL2 模块查找 SDL2
find_package(SDL2 REQUIRED)

# 尝试使用标准方式查找其他 SDL2 组件
if(WIN32)
    find_package(SDL2_image REQUIRED PATHS "${CMAKE_CURRENT_SOURCE_DIR}/lib/dep/plugins/SDL2_image/cmake")
    find_package(SDL2_ttf REQUIRED PATHS "${CMAKE_CURRENT_SOURCE_DIR}/lib/dep/plugins/SDL2_ttf/cmake")
    find_package(SDL2_mixer REQUIRED PATHS "${CMAKE_CURRENT_SOURCE_DIR}/lib/dep/plugins/SDL2_mixer/cmake")
elseif(ANDROID)
    find_package(SDL2_image QUIET)
    find_package(SDL2_ttf QUIET)
    find_package(SDL2_mixer QUIET)
else()
    find_package(SDL2_image REQUIRED)
    find_package(SDL2_ttf REQUIRED)
    find_package(SDL2_mixer REQUIRED)
endif()

add_executable(${PROJECT_NAME} main.cpp)

# 通用包含路径
target_include_directories(${PROJECT_NAME} PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/api/lyt/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/api/lx/include"
)

# 平台特定包含路径
if(SDL2_INCLUDE_DIRS)
    target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIRS})
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
    api/lx/src/ScoreManager.cpp
)

# 链接 SDL2 库
if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        SDL2
        SDL2main
        SDL2_image
        SDL2_ttf
        SDL2_mixer
    )

    # 确保 DLL 能够被找到
    if(SDL2_ARCH_PATH)
        target_link_directories(${PROJECT_NAME} PRIVATE "${SDL2_ARCH_PATH}")
    endif()
elseif(ANDROID)
    if(TARGET SDL2::SDL2)
        target_link_libraries(${PROJECT_NAME} PRIVATE
            SDL2::SDL2
            SDL2::SDL2main
        )
    endif()
    if(TARGET SDL2_image::SDL2_image)
        target_link_libraries(${PROJECT_NAME} PRIVATE SDL2_image::SDL2_image)
    endif()
    if(TARGET SDL2_ttf::SDL2_ttf)
        target_link_libraries(${PROJECT_NAME} PRIVATE SDL2_ttf::SDL2_ttf)
    endif()
    if(TARGET SDL2_mixer::SDL2_mixer)
        target_link_libraries(${PROJECT_NAME} PRIVATE SDL2_mixer::SDL2_mixer)
    endif()
else()
    target_link_libraries(${PROJECT_NAME} PRIVATE
        SDL2::SDL2
        SDL2::SDL2main
        SDL2_image::SDL2_image
        SDL2_ttf::SDL2_ttf
        SDL2_mixer::SDL2_mixer
    )
endif()
