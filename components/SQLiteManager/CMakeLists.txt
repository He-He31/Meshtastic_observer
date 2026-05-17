cmake_minimum_required(VERSION 3.22)

project(SQLiteManager)

add_library(SQLiteManager STATIC 
                    ./src/sqlite3.c
                    ./src/SQLiteManager.cpp)


target_include_directories(SQLiteManager PUBLIC include)
