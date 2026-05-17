cmake_minimum_required(VERSION 3.22)

project(Meshtastic_client)

add_subdirectory(components/SQLiteManager)
add_subdirectory(components/CLIManager)
add_subdirectory(components/LogManager)

add_executable(meshtastic_app main.cpp)


target_link_libraries(meshtastic_app PRIVATE SQLiteManager)
target_link_libraries(meshtastic_app PRIVATE CLI_MANAGER_LIB)
target_link_libraries(meshtastic_app PRIVATE LogManager)