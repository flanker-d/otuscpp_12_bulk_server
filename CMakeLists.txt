cmake_minimum_required(VERSION 3.9)
project(bulk_server)

set(CMAKE_CXX_STANDARD 14)
include_directories(${PROJECT_SOURCE_DIR})

add_library(bulk_server_common
        common/communications.h
        common/interface.h
        common/tcp/client_session.cpp
        common/tcp/server.cpp)
target_link_libraries(bulk_server_common -lboost_system)
target_link_libraries(bulk_server_common -lboost_thread)

add_library(bulk_server_mt
        mt/commands_storage.cpp
        mt/console_logger.cpp
        mt/file_logger.cpp
        mt/observer.h
        mt/command_processor.cpp
        mt/metricks.cpp)
target_link_libraries(bulk_server_mt -lpthread)

add_executable(bulk_server
        main.cpp
        bulk_server.cpp
        interpreter.cpp)
target_link_libraries(bulk_server bulk_server_mt)
target_link_libraries(bulk_server bulk_server_common)