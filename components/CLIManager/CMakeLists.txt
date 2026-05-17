cmake_minimum_required(VERSION 3.22)

project(CLI_MANAGER_LIB)


file(GLOB_RECURSE SRC src/*) 

add_library(CLI_MANAGER_LIB STATIC
                ${SRC})

target_include_directories(CLI_MANAGER_LIB PUBLIC include)