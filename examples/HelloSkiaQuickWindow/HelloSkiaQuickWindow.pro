TEMPLATE = app
QT += quick
include($$absolute_path($$PWD/../../QtSkia/QtSkiaQuickPublic.pri))
include($$absolute_path($$PWD/../Renderer/Renderer.pri))

CONFIG(debug, debug|release) {
    DESTDIR =$$absolute_path($$PWD/../../bin/debug)
} else {
    DESTDIR =$$absolute_path($$PWD/../../bin/release)
}
LIBS += -L$$DESTDIR -lQtSkiaQuick

HEADERS += \
    SkiaQuickWindow.h

SOURCES += \
    main.cpp
