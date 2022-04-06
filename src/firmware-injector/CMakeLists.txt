cmake_minimum_required(VERSION 3.0.0)

project(firmware-injector VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)

set(UEFITOOL_SOURCES ${PROJECT_SOURCE_DIR}/../../deps/UEFITool/common/guiddatabase.cpp
                     ${PROJECT_SOURCE_DIR}/../../deps/UEFITool/common/types.cpp
                     ${PROJECT_SOURCE_DIR}/../../deps/UEFITool/common/descriptor.cpp
                     ${PROJECT_SOURCE_DIR}/../../deps/UEFITool/common/ffs.cpp
                     ${PROJECT_SOURCE_DIR}/../../deps/UEFITool/common/ffsutils.cpp
                     ${PROJECT_SOURCE_DIR}/../../deps/UEFITool/common/nvram.cpp
                     ${PROJECT_SOURCE_DIR}/../../deps/UEFITool/common/nvramparser.cpp
                     ${PROJECT_SOURCE_DIR}/../../deps/UEFITool/common/meparser.cpp
                     ${PROJECT_SOURCE_DIR}/../../deps/UEFITool/common/ffsparser.cpp
                     ${PROJECT_SOURCE_DIR}/../../deps/UEFITool/common/ffsreport.cpp
                     ${PROJECT_SOURCE_DIR}/../../deps/UEFITool/common/peimage.cpp
                     ${PROJECT_SOURCE_DIR}/../../deps/UEFITool/common/treeitem.cpp
                     ${PROJECT_SOURCE_DIR}/../../deps/UEFITool/common/treemodel.cpp
                     ${PROJECT_SOURCE_DIR}/../../deps/UEFITool/common/utility.cpp
                     ${PROJECT_SOURCE_DIR}/../../deps/UEFITool/common/LZMA/LzmaDecompress.c
                     ${PROJECT_SOURCE_DIR}/../../deps/UEFITool/common/LZMA/SDK/C/Bra86.c
                     ${PROJECT_SOURCE_DIR}/../../deps/UEFITool/common/LZMA/SDK/C/LzmaDec.c
                     ${PROJECT_SOURCE_DIR}/../../deps/UEFITool/common/Tiano/EfiTianoDecompress.c
                     ${PROJECT_SOURCE_DIR}/../../deps/UEFITool/common/ustring.cpp
                     ${PROJECT_SOURCE_DIR}/../../deps/UEFITool/common/sha256.c
                     ${PROJECT_SOURCE_DIR}/../../deps/UEFITool/common/bstrlib/bstrlib.c
                     ${PROJECT_SOURCE_DIR}/../../deps/UEFITool/common/bstrlib/bstrwrap.cpp
                     ${PROJECT_SOURCE_DIR}/../../deps/UEFITool/common/zlib/adler32.c
                     ${PROJECT_SOURCE_DIR}/../../deps/UEFITool/common/zlib/compress.c
                     ${PROJECT_SOURCE_DIR}/../../deps/UEFITool/common/zlib/crc32.c
                     ${PROJECT_SOURCE_DIR}/../../deps/UEFITool/common/zlib/deflate.c
                     ${PROJECT_SOURCE_DIR}/../../deps/UEFITool/common/zlib/gzclose.c
                     ${PROJECT_SOURCE_DIR}/../../deps/UEFITool/common/zlib/gzlib.c
                     ${PROJECT_SOURCE_DIR}/../../deps/UEFITool/common/zlib/gzread.c
                     ${PROJECT_SOURCE_DIR}/../../deps/UEFITool/common/zlib/gzwrite.c
                     ${PROJECT_SOURCE_DIR}/../../deps/UEFITool/common/zlib/inflate.c
                     ${PROJECT_SOURCE_DIR}/../../deps/UEFITool/common/zlib/infback.c
                     ${PROJECT_SOURCE_DIR}/../../deps/UEFITool/common/zlib/inftrees.c
                     ${PROJECT_SOURCE_DIR}/../../deps/UEFITool/common/zlib/inffast.c
                     ${PROJECT_SOURCE_DIR}/../../deps/UEFITool/common/zlib/trees.c
                     ${PROJECT_SOURCE_DIR}/../../deps/UEFITool/common/zlib/uncompr.c
                     ${PROJECT_SOURCE_DIR}/../../deps/UEFITool/common/zlib/zutil.c
)

set(UEFI_INCLUDES ${PROJECT_SOURCE_DIR}/../../deps)

add_executable(firmware-injector ${PROJECT_SOURCE_DIR}/main.cpp
                                 ${UEFITOOL_SOURCES}
)

target_include_directories(firmware-injector PRIVATE ${UEFI_INCLUDES})

target_compile_definitions(firmware-injector PRIVATE U_ENABLE_NVRAM_PARSING_SUPPORT
                                                     U_ENABLE_ME_PARSING_SUPPORT
                                                     U_ENABLE_FIT_PARSING_SUPPORT
                                                     U_ENABLE_GUID_DATABASE_SUPPORT
)