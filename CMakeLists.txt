cmake_minimum_required(VERSION 3.0.0)

project(uefi-rootkit VERSION 0.1.0)

set(CMAKE_SYSTEM_NAME Windows)

add_executable(payload WIN32 ${PROJECT_SOURCE_DIR}/src/payload/main.cpp)

target_link_options(payload PRIVATE -static)