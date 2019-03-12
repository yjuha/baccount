cmake_minimum_required(VERSION 3.4)

set(APP baccount)

project(${APP})

add_executable(${APP} main.cpp)

target_include_directories(${APP} PRIVATE ${PROJECT_SOURCE_DIR}/include)
