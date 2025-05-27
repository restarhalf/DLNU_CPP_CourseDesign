cmake_minimum_required(VERSION 3.29)
project(DLNU_CPP_CourseDesign)

set(CMAKE_CXX_STANDARD 17)

# 添加SDL2路径配置
set(SDL2_DIR ${PROJECT_SOURCE_DIR}/SDL2-2.32.6/cmake)
find_package(SDL2 REQUIRED)

add_executable(DLNU_CPP_CourseDesign main.cpp
)

# 链接SDL2库
target_link_libraries(DLNU_CPP_CourseDesign
    PRIVATE
    SDL2::SDL2
)