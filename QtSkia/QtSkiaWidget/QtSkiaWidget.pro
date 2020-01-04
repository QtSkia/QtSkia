TEMPLATE = lib
QT += widgets
DEFINES += QTSKIA_LIBRARY

include($$PWD/../QtSkiaWidgetPublic.pri)

CONFIG(debug, debug|release) {
    DESTDIR =$$absolute_path($$PWD/../../bin/debug)
} else {
    DESTDIR =$$absolute_path($$PWD/../../bin/release)
}

HEADERS += \
    QSkiaWidget.h \
    QSkiaOpenGLWidget.h

SOURCES += \
    QSkiaWidget.cpp \
    QSkiaOpenGLWidget.cpp
