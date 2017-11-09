cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
cmake_policy(SET CMP0054 OLD)
cmake_policy(SET CMP0045 OLD)

project(gnl C)

set(BUILD_SHARED_LIBS OFF)

set(gnl_INC_DIR ${CMAKE_CURRENT_LIST_DIR})
set(gnl_SRC_DIR ${CMAKE_CURRENT_LIST_DIR})

set(CMAKE_C_FLAGS "")
set(CMAKE_C_FLAGS_DEBUG "")
set(CMAKE_C_FLAGS_RELEASE "")

add_library(gnl get_next_line.c get_next_line.h)
set_property(TARGET gnl PROPERTY C_STANDARD 90)
target_include_directories(gnl PUBLIC ${gnl_INC_DIR})
target_include_directories(gnl PUBLIC ft)

target_compile_definitions(gnl
  PRIVATE $<$<CONFIG:Debug>:DEBUG>$<$<CONFIG:Release>:NDEBUG>
  PRIVATE API_COMPILE)
if (MSVC)
  target_compile_options(gnl
    PRIVATE /MT$<$<CONFIG:Debug>:d> /Oy /W3
    PRIVATE /D_CRT_SECURE_NO_WARNINGS /Dinline=__inline
    PRIVATE /O$<$<CONFIG:Debug>:d>$<$<CONFIG:Release>:x>)
else ()
  target_compile_options(gnl
    PRIVATE -Wall -Werror -Wextra -fomit-frame-pointer -ansi
    PRIVATE -Wno-missing-field-initializers -Wno-missing-braces
    PRIVATE -O$<$<CONFIG:Debug>:0 -g3>$<$<CONFIG:Release>:3>)
endif ()
