win32 {
#    GN=$$system_path($$PWD/windows/gn.exe)
#    NINJA=$$system_path($$PWD/windows/ninja.exe)
    GN=gn.exe
    NINJA=ninja.exe
}
macos {
    GN=$$system_path($$PWD/macos/gn)
    NINJA=$$system_path($$PWD/macos/ninja)
}
linux {
    GN=$$system_path($$PWD/linux/gn)
    NINJA=$$system_path($$PWD/linux/ninja)
}
CONFIG(debug, debug|release) {
    verbose_flags = -v
    gn_args += is_debug=true
} else {
    verbose_flags =
    gn_args += is_debug=false
}

gn_args += \
    is_official_build=false \
    is_component_build=true \
    win_vc=\"C:\\Program Files (x86)\\Microsoft Visual Studio\\2017\\Enterprise\\VC\"

msvc:clang_cl {
    gn_args += clang_win=\"C:\\Program Files\\LLVM\"
}
