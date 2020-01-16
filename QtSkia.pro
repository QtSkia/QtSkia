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
    *.md \
    LICENSE \
    .clang-format \
    .qmake.conf \
    syncSkia* \
    .github/workflows/*.yml
