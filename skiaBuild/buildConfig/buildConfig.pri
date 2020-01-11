CONFIG(debug, debug|release) {
    verbose_flags = -v
} else {
    verbose_flags =
}
win32 {
    include($$PWD/windows.pri)
}
macos {
    include($$PWD/macos.pri)
}
#ios {
#    include($$PWD/ios.pri)
#}
#android {
#    include($$PWD/android.pri)
#}
linux {
    include($$PWD/linux.pri)
}
#wasm {
#    include($$PWD/wasm.pri)
#}
