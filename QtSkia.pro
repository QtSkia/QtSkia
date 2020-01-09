TEMPLATE = subdirs

SUBDIRS += \
    skiaBuild \
    QtSkia \
    examples \
    tests
CONFIG += ordered

OTHER_FILES += \
    skiacommon.pri \
    uniqueDestdir.pri \
    README.md \
    LICENSE \
    .clang-format \
    .qmake.conf \
    .github/workflows/*.yml
