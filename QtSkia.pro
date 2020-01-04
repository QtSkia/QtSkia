TEMPLATE = subdirs

SUBDIRS += \
    skiaBuild \
    QtSkia \
    examples \
    tests
CONFIG += ordered

OTHER_FILES += \
    README.md \
    .clang-format \
    LICENSE
