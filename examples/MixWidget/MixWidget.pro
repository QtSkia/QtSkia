QT       += core gui widgets

include($$absolute_path($$PWD/../../QtSkia/QtSkiaWidgetPublic.pri))

CONFIG(debug, debug|release) {
    DESTDIR =$$absolute_path($$PWD/../../bin/debug)
} else {
    DESTDIR =$$absolute_path($$PWD/../../bin/release)
}
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
