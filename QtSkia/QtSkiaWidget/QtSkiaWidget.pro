TEMPLATE = lib
QT += widgets
DEFINES += QTSKIA_LIBRARY

include($$PWD/../QtSkiaWidgetPublic.pri)

include($$PWD/../../uniqueDestdir.pri)
DESTDIR = $$destPath

HEADERS += \
    QSkiaWidget.h \
    QSkiaOpenGLWidget.h

SOURCES += \
    QSkiaWidget.cpp \
    QSkiaOpenGLWidget.cpp
