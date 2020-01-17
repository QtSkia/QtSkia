TEMPLATE = lib
QT += quick
DEFINES += QTSKIA_LIBRARY

include($$absolute_path($$PWD/../QtSkiaQuickPublic.pri))

include($$PWD/../../uniqueDestdir.pri)
DESTDIR = $$destPath
HEADERS += \
    LottieItem/QSkiaLottieItem.h \
    QuickWindow/QSkiaQuickWindow.h \
    QuickItem/QSkiaQuickItem.h

SOURCES += \
    LottieItem/QSkiaLottieItem.cpp \
    QuickWindow/QSkiaQuickWindow.cpp \
    QuickItem/QSkiaQuickItem.cpp
LIBS += -lskottie
