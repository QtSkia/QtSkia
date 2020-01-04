TEMPLATE = lib
QT += quick
DEFINES += QTSKIA_LIBRARY

include($$absolute_path($$PWD/../QtSkiaQuickPublic.pri))

CONFIG(debug, debug|release) {
    DESTDIR =$$absolute_path($$PWD/../../bin/debug)
} else {
    DESTDIR =$$absolute_path($$PWD/../../bin/release)
}
HEADERS += \
    QSkiaQuickWindow.h \
    QSkiaQuickItem.h

SOURCES += \
    QSkiaQuickWindow.cpp \
    QSkiaQuickItem.cpp
