TEMPLATE = lib
DEFINES += QTSKIA_LIBRARY

include($$absolute_path($$PWD/../QtSkiaWindowPublic.pri))

CONFIG(debug, debug|release) {
    DESTDIR =$$absolute_path($$PWD/../../bin/debug)
} else {
    DESTDIR =$$absolute_path($$PWD/../../bin/release)
}
HEADERS += \
    QSkiaOpenGLWindow.h \
    QSkiaVulkanWindow.h

SOURCES += \
    QSkiaOpenGLWindow.cpp \
    QSkiaVulkanWindow.cpp

