TEMPLATE = app
QT += quick
include($$absolute_path($$PWD/../../QtSkia/QtSkiaQuickPublic.pri))
include($$absolute_path($$PWD/../Renderer/Renderer.pri))

include($$PWD/../../uniqueDestdir.pri)
DESTDIR = $$destPath

LIBS += -L$$DESTDIR -lQtSkiaQuick

HEADERS += \
    SkiaQuickWindow.h

SOURCES += \
    main.cpp
