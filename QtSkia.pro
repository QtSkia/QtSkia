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
    .clang-format \
    LICENSE \
    .github/workflows/*.yml
