cmake_minimum_required(VERSION 3.22)

project(LogManager)

file(GLOB_RECURSE SRC src/*)

add_library(LogManager STATIC ${SRC})
target_include_directories(LogManager PUBLIC include)


