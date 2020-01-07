TEMPLATE = app
QT += widgets

include($$absolute_path($$PWD/../../QtSkia/QtSkiaWidgetPublic.pri))
include($$absolute_path($$PWD/../Renderer/Renderer.pri))

include($$PWD/../../uniqueDestdir.pri)
DESTDIR = $$destPath
LIBS += -L$$DESTDIR -lQtSkiaWidget

HEADERS += \
    SkiaGLWidget.h

SOURCES += \
    main.cpp
