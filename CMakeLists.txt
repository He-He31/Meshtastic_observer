cmake_minimum_required(VERSION 3.22)

project(Meshtastic_client)

add_subdirectory(components/SQLiteManager)

add_executable(meshtastic_app main.cpp)
target_link_libraries(meshtastic_app PRIVATE SQLiteManager)