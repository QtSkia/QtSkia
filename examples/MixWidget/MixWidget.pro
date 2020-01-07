QT       += core gui widgets

include($$absolute_path($$PWD/../../QtSkia/QtSkiaWidgetPublic.pri))

include($$PWD/../../uniqueDestdir.pri)
DESTDIR = $$destPath

LIBS += -L$$DESTDIR -lQtSkiaWidget

SOURCES += \
    SkWidget.cpp \
    main.cpp \
    MainWindow.cpp

HEADERS += \
    MainWindow.h \
    SkWidget.h

FORMS += \
    MainWindow.ui
