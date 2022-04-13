cmake_minimum_required(VERSION 3.0.0)

project(firmware-patcher VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 COMPONENTS Core REQUIRED)

add_executable(firmware-patcher main.cpp
                               ${PROJECT_SOURCE_DIR}/../../deps/UEFITool/types.cpp
                               ${PROJECT_SOURCE_DIR}/../../deps/UEFITool/descriptor.cpp
                               ${PROJECT_SOURCE_DIR}/../../deps/UEFITool/ffs.cpp
                               ${PROJECT_SOURCE_DIR}/../../deps/UEFITool/ffsengine.cpp
                               ${PROJECT_SOURCE_DIR}/../../deps/UEFITool/peimage.cpp
                               ${PROJECT_SOURCE_DIR}/../../deps/UEFITool/treeitem.cpp
                               ${PROJECT_SOURCE_DIR}/../../deps/UEFITool/treemodel.cpp
                               ${PROJECT_SOURCE_DIR}/../../deps/UEFITool/LZMA/LzmaCompress.c
                               ${PROJECT_SOURCE_DIR}/../../deps/UEFITool/LZMA/LzmaDecompress.c
                               ${PROJECT_SOURCE_DIR}/../../deps/UEFITool/LZMA/SDK/C/LzFind.c
                               ${PROJECT_SOURCE_DIR}/../../deps/UEFITool/LZMA/SDK/C/LzmaDec.c
                               ${PROJECT_SOURCE_DIR}/../../deps/UEFITool/LZMA/SDK/C/LzmaEnc.c
                               ${PROJECT_SOURCE_DIR}/../../deps/UEFITool/LZMA/SDK/C/Bra86.c
                               ${PROJECT_SOURCE_DIR}/../../deps/UEFITool/Tiano/EfiTianoDecompress.c
                               ${PROJECT_SOURCE_DIR}/../../deps/UEFITool/Tiano/EfiTianoCompress.c
                               ${PROJECT_SOURCE_DIR}/../../deps/UEFITool/Tiano/EfiTianoCompressLegacy.c
)

target_include_directories(firmware-patcher PRIVATE ${PROJECT_SOURCE_DIR}/../../deps
                                                   ${PROJECT_SOURCE_DIR}/../../deps/Tiano
                                                   ${PROJECT_SOURCE_DIR}/../../deps/LZMA
)

target_link_libraries(firmware-patcher PRIVATE Qt5::Core)

target_compile_definitions(firmware-patcher PRIVATE _CONSOLE)