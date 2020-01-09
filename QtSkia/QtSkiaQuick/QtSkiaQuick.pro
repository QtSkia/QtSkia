TEMPLATE = lib
QT += quick quick-private
DEFINES += QTSKIA_LIBRARY

include($$absolute_path($$PWD/../QtSkiaQuickPublic.pri))

include($$PWD/../../uniqueDestdir.pri)
DESTDIR = $$destPath
HEADERS += \
    InnerItem_p.h \
    QSkiaQuickWindow.h \
    QSkiaQuickItem.h

SOURCES += \
    QSkiaQuickWindow.cpp \
    QSkiaQuickItem.cpp
