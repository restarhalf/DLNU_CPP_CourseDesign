cmake_minimum_required(VERSION 3.29)
project("DLNU_CPP_CourseDesign")

set(CMAKE_CXX_STANDARD 20)

# 添加资源文件
set(RESOURCE_FILES resource.rc)

add_executable(${PROJECT_NAME} main.cpp
)

# 设置 Windows 子系统，使程序以 GUI 方式运行
if(WIN32)
    set_target_properties(${PROJECT_NAME} PROPERTIES
            WIN32_EXECUTABLE TRUE
            LINK_FLAGS "/ENTRY:mainCRTStartup"
    )
endif()

target_include_directories(${PROJECT_NAME} PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/lib/dep/plugins/SDL2/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/api/lyt/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/api/lx/include")

target_link_directories(${PROJECT_NAME} PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/lib/dep/plugins/SDL2/lib/x64")

target_sources(${PROJECT_NAME} PRIVATE
        api/lyt/src/Button.cpp
        api/lyt/src/Game.cpp
        api/lyt/src/Image.cpp
        api/lyt/src/Text.cpp
        api/lyt/src/Window.cpp
        api/lyt/src/Music.cpp
        api/lyt/src/Renderer.cpp
        api/lyt/src/Controller.cpp
        api/lyt/src/ResourceLoader.cpp  # 添加 ResourceLoader.cpp
        api/lx/src/Fish.cpp
        api/lx/src/PlayerFish.cpp
        api/lx/src/AIFish.cpp
        api/lx/src/ScoreManager.cpp
)

target_link_libraries(DLNU_CPP_CourseDesign PRIVATE
        SDL2
        SDL2main
        SDL2_image
        SDL2_ttf
        SDL2_mixer
)

# 复制 SDL2 DLL 到构建目录
if(WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_SOURCE_DIR}/lib/dep/plugins/SDL2/lib/x64/SDL2.dll"
            "${CMAKE_CURRENT_SOURCE_DIR}/lib/dep/plugins/SDL2/lib/x64/SDL2_image.dll"
            "${CMAKE_CURRENT_SOURCE_DIR}/lib/dep/plugins/SDL2/lib/x64/SDL2_ttf.dll"
            "${CMAKE_CURRENT_SOURCE_DIR}/lib/dep/plugins/SDL2/lib/x64/SDL2_mixer.dll"
            $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
endif()

