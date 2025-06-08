# FindSDL2.cmake
# ---------
#
# 寻找 SDL2 库并设置标准变量
# 此模块会定义以下变量:
#
# SDL2_INCLUDE_DIRS - SDL2 头文件目录
# SDL2_LIBRARIES - SDL2 链接库
# SDL2_FOUND - 如果找到了 SDL2，设置为 TRUE
#

# 尝试使用 pkg-config 定位 SDL2
find_package(PkgConfig QUIET)
if(PKG_CONFIG_FOUND)
  pkg_check_modules(SDL2 QUIET sdl2)
endif()

# 如果 pkg-config 没找到，尝试寻找头文件和库文件
if(NOT SDL2_FOUND)
  # 寻找 SDL2 头文件
  find_path(SDL2_INCLUDE_DIR
    NAMES SDL.h
    HINTS
      ENV SDL2DIR
      ${SDL2_BASE} # 由 CMakeLists.txt 设置
    PATH_SUFFIXES SDL2 include/SDL2 include
  )

  # 寻找 SDL2 库
  if(WIN32)
    # Windows 平台找特定的库文件名
    find_library(SDL2_LIBRARY
      NAMES SDL2
      HINTS
        ENV SDL2DIR
        ${SDL2_BASE}
      PATH_SUFFIXES lib ${SDL2_LIB_DIR} lib/x64 lib/x86
    )
    find_library(SDL2MAIN_LIBRARY
      NAMES SDL2main
      HINTS
        ENV SDL2DIR
        ${SDL2_BASE}
      PATH_SUFFIXES lib ${SDL2_LIB_DIR} lib/x64 lib/x86
    )
  else()
    # 非 Windows 平台
    find_library(SDL2_LIBRARY
      NAMES SDL2
      HINTS
        ENV SDL2DIR
      PATH_SUFFIXES lib lib64 lib/x64 lib/${CMAKE_LIBRARY_ARCHITECTURE}
    )
    find_library(SDL2MAIN_LIBRARY
      NAMES SDL2main
      HINTS
        ENV SDL2DIR
      PATH_SUFFIXES lib lib64 lib/x64 lib/${CMAKE_LIBRARY_ARCHITECTURE}
    )
  endif()

  # 检查是否找到了头文件和库文件
  if(SDL2_INCLUDE_DIR AND SDL2_LIBRARY)
    set(SDL2_FOUND TRUE)
    set(SDL2_INCLUDE_DIRS ${SDL2_INCLUDE_DIR})
    if(SDL2MAIN_LIBRARY)
      set(SDL2_LIBRARIES ${SDL2MAIN_LIBRARY} ${SDL2_LIBRARY})
    else()
      set(SDL2_LIBRARIES ${SDL2_LIBRARY})
    endif()
  endif()
endif()

# 处理查找结果
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(SDL2
  REQUIRED_VARS SDL2_LIBRARY SDL2_INCLUDE_DIR
  VERSION_VAR SDL2_VERSION)

# 创建导入目标
if(SDL2_FOUND AND NOT TARGET SDL2::SDL2)
  add_library(SDL2::SDL2 SHARED IMPORTED)
  set_target_properties(SDL2::SDL2 PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${SDL2_INCLUDE_DIRS}")

  if(WIN32)
    set_target_properties(SDL2::SDL2 PROPERTIES
      IMPORTED_IMPLIB "${SDL2_LIBRARY}")
  else()
    set_target_properties(SDL2::SDL2 PROPERTIES
      IMPORTED_LOCATION "${SDL2_LIBRARY}")
  endif()

  # SDL2main 在某些平台上是必要的
  if(SDL2MAIN_LIBRARY AND NOT TARGET SDL2::SDL2main)
    add_library(SDL2::SDL2main STATIC IMPORTED)
    set_target_properties(SDL2::SDL2main PROPERTIES
      IMPORTED_LOCATION "${SDL2MAIN_LIBRARY}")
  endif()
endif()

mark_as_advanced(
  SDL2_INCLUDE_DIR
  SDL2_LIBRARY
  SDL2MAIN_LIBRARY
)
