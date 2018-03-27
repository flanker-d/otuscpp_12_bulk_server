cmake_minimum_required(VERSION 3.2)

project(bulk_server VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

include_directories(${PROJECT_SOURCE_DIR})

configure_file(version.h.in version.h)

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

set_target_properties(bulk_server_common bulk_server_mt bulk_server PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        COMPILE_OPTIONS -Wpedantic -Wall -Wextra
        )

install(TARGETS bulk_server_common bulk_server_mt bulk_server
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT artyom.sorokoumov@gmail.com)

include(CPack)
