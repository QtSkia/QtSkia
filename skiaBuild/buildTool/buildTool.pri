win32 {
    GN=$$system_path($$PWD/windows/gn.exe)
    NINJA=$$system_path($$PWD/windows/ninja.exe)
}
macos|ios {
    GN=$$system_path($$PWD/macos/gn)
    NINJA=$$system_path($$PWD/macos/ninja)
}
linux|android {
    GN=$$system_path($$PWD/linux/gn)
    NINJA=$$system_path($$PWD/linux/ninja)
}

