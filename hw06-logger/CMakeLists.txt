cmake_minimum_required(VERSION 3.25)
project(lib_demo C)

add_compile_options(-Wall -Wextra -Wpedantic)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED true)
ADD_LINK_OPTIONS(-rdynamic)

add_library(logger STATIC
  lib/log_internal.c lib/log_internal.h
  lib/log_helper.c lib/log_helper.h
	lib/logapi.c lib/logapi.h
)
set_target_properties(logger PROPERTIES PUBLIC_HEADER lib/logger.h)

add_executable(lib_demo main.c)
target_link_libraries(lib_demo logger)
