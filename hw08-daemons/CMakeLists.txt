cmake_minimum_required(VERSION 3.25)
project(demons)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED true)

include_directories(
  ${PROJECT_SOURCE_DIR}/src
)

file(GLOB SRC
  "${PROJECT_SOURCE_DIR}/src/*.h"
  "${PROJECT_SOURCE_DIR}/src/*.c"
)
add_executable(daemons ${SRC} main.c)
