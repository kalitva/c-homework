cmake_minimum_required(VERSION 3.25)
project(lib_demo)

add_compile_options(-Wall -Wextra -Wpedantic)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED true)

add_library(logger STATIC
  lib/logger.c lib/logger.h
  lib/log_helper.c lib/log_helper.h
)
set_target_properties(logger PROPERTIES PUBLIC_HEADER lib/logger.h)

add_executable(lib_demo main.c)
target_link_libraries(lib_demo logger)
