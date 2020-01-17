TEMPLATE = app
QT += quick
include($$absolute_path($$PWD/../../QtSkia/QtSkiaQuickPublic.pri))

include($$PWD/../../uniqueDestdir.pri)
DESTDIR = $$destPath

LIBS += -L$$DESTDIR -lQtSkiaQuick
DEFINES += resPath=\\\"file:///$$absolute_path($$PWD)\\\"

SOURCES += \
    main.cpp

RESOURCES += \
    Qml.qrc
