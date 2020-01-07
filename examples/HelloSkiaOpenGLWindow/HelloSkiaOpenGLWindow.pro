TEMPLATE = app

include($$absolute_path($$PWD/../../QtSkia/QtSkiaWindowPublic.pri))
include($$absolute_path($$PWD/../Renderer/Renderer.pri))

include($$PWD/../../uniqueDestdir.pri)
DESTDIR = $$destPath
LIBS += -L$$DESTDIR -lQtSkiaWindow

HEADERS += \
    SkiaGLWindow.h

SOURCES += \
    main.cpp
