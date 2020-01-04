TEMPLATE = app

include($$absolute_path($$PWD/../../skiaCommon.pri))
include($$absolute_path($$PWD/../../QtSkia/QtSkiaWindowPublic.pri))
include($$absolute_path($$PWD/../Renderer/Renderer.pri))

CONFIG(debug, debug|release) {
    DESTDIR =$$absolute_path($$PWD/../../bin/debug)
} else {
    DESTDIR =$$absolute_path($$PWD/../../bin/release)
}
LIBS += -L$$DESTDIR -lQtSkiaWindow

HEADERS += \
    SkiaGLWindow.h

SOURCES += \
    main.cpp
