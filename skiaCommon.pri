QT += core gui

CONFIG += c++17

msvc {
    QMAKE_CFLAGS += -source-charset:utf-8
    QMAKE_CXXFLAGS += -source-charset:utf-8
}
include(uniqueDestdir.pri)
SKIA_OUT_PATH=$$destPath
SKIA_SRC_PATH=$$absolute_path($$PWD/3rdparty/skia)
SKIA_LIB_PATH=$$SKIA_OUT_PATH
SKIA_INCLUDE_PATH=$$SKIA_SRC_PATH/include

DEFINES +=SKIA_DLL QT_NO_FOREACH

INCLUDEPATH +=$$SKIA_SRC_PATH $$SKIA_INCLUDE_PATH

DEPENDPATH +=$$SKIA_LIB_PATH
LIBS += -L$$SKIA_LIB_PATH -lskia.dll
