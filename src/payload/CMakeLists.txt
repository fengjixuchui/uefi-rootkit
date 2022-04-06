cmake_minimum_required(VERSION 3.0.0)

project(payload VERSION 0.1.0)

set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_CXX_STANDARD 20)

add_executable(payload WIN32 ${PROJECT_SOURCE_DIR}/main.cpp)

target_link_options(payload PRIVATE -static)

#add_custom_command(payload POST_BUILD COMMAND echo "Hel" ARGS $<TARGET_FILE>)