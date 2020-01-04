TEMPLATE = lib
QT += widgets
DEFINES += QTSKIA_LIBRARY

include($$absolute_path($$PWD/../../SkiaCommon.pri))

CONFIG(debug, debug|release) {
    DESTDIR =$$absolute_path($$PWD/../../../bin/debug)
} else {
    DESTDIR =$$absolute_path($$PWD/../../../bin/release)
}
include(QtSkiaWidgetPublic.pri)
HEADERS += \
    $$absolute_path($$PWD/../QtSkia_global.h) \
    QSkiaWidget.h \
    QSkiaOpenGLWidget.h

SOURCES += \
    QSkiaWidget.cpp \
    QSkiaOpenGLWidget.cpp
