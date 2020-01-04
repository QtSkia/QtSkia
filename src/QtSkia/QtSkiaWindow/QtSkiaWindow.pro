TEMPLATE = lib
DEFINES += QTSKIA_LIBRARY

include($$absolute_path($$PWD/../../SkiaCommon.pri))

CONFIG(debug, debug|release) {
    DESTDIR =$$absolute_path($$PWD/../../../bin/debug)
} else {
    DESTDIR =$$absolute_path($$PWD/../../../bin/release)
}
include(QtSkiaWindowPublic.pri)
HEADERS += \
    $$absolute_path($$PWD/../QtSkia_global.h) \
    QSkiaOpenGLWindow.h \
    QSkiaVulkanWindow.h

SOURCES += \
    QSkiaOpenGLWindow.cpp \
    QSkiaVulkanWindow.cpp

