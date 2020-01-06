TEMPLATE = subdirs

SUBDIRS += \
    skiaBuild \
    QtSkia \
    examples \
    tests
CONFIG += ordered

OTHER_FILES += \
    skiacommon.pri \
    README.md \
    .clang-format \
    LICENSE
