TEMPLATE = lib
QT += quick
DEFINES += QTSKIA_LIBRARY

include($$absolute_path($$PWD/../QtSkiaQuickPublic.pri))

include($$PWD/../../uniqueDestdir.pri)
DESTDIR = $$destPath
HEADERS += \
    QuickWindow/QSkiaQuickWindow.h \
    QuickItem/QSkiaQuickItem.h

SOURCES += \
    QuickWindow/QSkiaQuickWindow.cpp \
    QuickItem/QSkiaQuickItem.cpp
