cmake_minimum_required(VERSION 3.25)
project(gtk C)

add_compile_options(-Wall -Wextra -Wpedantic)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED true)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK REQUIRED gtk+-3.0)
include_directories(${GTK_INCLUDE_DIRS})
link_directories(${GTK_LIBRARY_DIRS})
add_executable(gtk main.c)
target_link_libraries(gtk ${GTK_LIBRARIES})
