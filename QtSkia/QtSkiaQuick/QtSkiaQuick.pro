TEMPLATE = lib
QT += quick
DEFINES += QTSKIA_LIBRARY

include($$absolute_path($$PWD/../QtSkiaQuickPublic.pri))

include($$PWD/../../uniqueDestdir.pri)
DESTDIR = $$destPath

HEADERS += \
    QSkiaQuickWindow.h \
    QSkiaQuickItem.h

SOURCES += \
    QSkiaQuickWindow.cpp \
    QSkiaQuickItem.cpp
