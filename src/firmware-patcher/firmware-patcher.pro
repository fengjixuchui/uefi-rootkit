QT       += core
QT       -= gui

TARGET    = firmware-patcher
TEMPLATE  = app
CONFIG   += console
CONFIG   -= app_bundle
DEFINES  += _CONSOLE

release: DESTDIR = ../../build/release
debug:   DESTDIR = ../../build/debug

OBJECTS_DIR = $$DESTDIR/.obj
MOC_DIR     = $$DESTDIR/.moc
RCC_DIR     = $$DESTDIR/.qrc
UI_DIR      = $$DESTDIR/.ui

SOURCES  += main.cpp \
            ../../deps/UEFITool/types.cpp \
            ../../deps/UEFITool/descriptor.cpp \
            ../../deps/UEFITool/ffs.cpp \
            ../../deps/UEFITool/ffsengine.cpp \
            ../../deps/UEFITool/peimage.cpp \
            ../../deps/UEFITool/treeitem.cpp \
            ../../deps/UEFITool/treemodel.cpp \
            ../../deps/UEFITool/LZMA/LzmaCompress.c \
            ../../deps/UEFITool/LZMA/LzmaDecompress.c \
            ../../deps/UEFITool/LZMA/SDK/C/LzFind.c \
            ../../deps/UEFITool/LZMA/SDK/C/LzmaDec.c \
            ../../deps/UEFITool/LZMA/SDK/C/LzmaEnc.c \
            ../../deps/UEFITool/LZMA/SDK/C/Bra86.c \
            ../../deps/UEFITool/Tiano/EfiTianoDecompress.c \
            ../../deps/UEFITool/Tiano/EfiTianoCompress.c \
            ../../deps/UEFITool/Tiano/EfiTianoCompressLegacy.c

HEADERS  += ../../deps/UEFITool/basetypes.h \
            ../../deps/UEFITool/descriptor.h \
            ../../deps/UEFITool/gbe.h \
            ../../deps/UEFITool/me.h \
            ../../deps/UEFITool/ffs.h \
            ../../deps/UEFITool/peimage.h \
            ../../deps/UEFITool/types.h \
            ../../deps/UEFITool/ffsengine.h \
            ../../deps/UEFITool/treeitem.h \
            ../../deps/UEFITool/treemodel.h \
            ../../deps/UEFITool/version.h \
            ../../deps/UEFITool/LZMA/LzmaCompress.h \
            ../../deps/UEFITool/LZMA/LzmaDecompress.h \
            ../../deps/UEFITool/LZMA/x86Convert.h \
            ../../deps/UEFITool/Tiano/EfiTianoDecompress.h \
            ../../deps/UEFITool/Tiano/EfiTianoCompress.h