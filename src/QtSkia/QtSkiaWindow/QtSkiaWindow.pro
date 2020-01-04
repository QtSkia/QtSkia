TEMPLATE = lib

include($$PWD/../../SkiaCommon.pri)

DEFINES += QTSKIA_LIBRARY

HEADERS += QSkiaQuickItem.h

SOURCES += QSkiaQuickItem.cpp

CONFIG(debug, debug|release) {
    DESTDIR =$$absolute_path($$PWD/../../../bin/debug)
} else {
    DESTDIR =$$absolute_path($$PWD/../../../bin/release)
}