TEMPLATE = lib
QT += quick
DEFINES += QTSKIA_LIBRARY

include($$absolute_path($$PWD/../QtSkiaQuickPublic.pri))

include($$PWD/../../uniqueDestdir.pri)
DESTDIR = $$destPath
HEADERS += \
    QuickItem/SkiaRenderNode.h \
    QuickWindow/InnerItem_p.h \
    QuickWindow/QSkiaQuickWindow.h \
    QuickItem/QSkiaQuickItem.h

SOURCES += \
    QuickItem/SkiaRenderNode.cpp \
    QuickWindow/QSkiaQuickWindow.cpp \
    QuickItem/QSkiaQuickItem.cpp
