win32 {
    GN=$$system_path($$PWD/windows/gn.exe)
    NINJA=$$system_path($$PWD/windows/ninja.exe)
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
    gn_args += \
        is_official_build=false \
        is_debug=true
} else {
    verbose_flags =
    gn_args += \
        is_official_build=false \
        is_debug=false
}
if($$QtSkia_Static_Build) {
    gn_args += \
        is_component_build=false
} else {
    gn_args += \
        is_component_build=true
}

msvc {
    gn_args += \
        win_vc=\"$$clean_path($$(VCINSTALLDIR))\" \
        win_toolchain_version=\"$$(VCToolsVersion)\" \
        win_sdk_version=\"$$clean_path($$(WindowsSDKVersion))\"
}

msvc:clang_cl {
    exists("$$(VCINSTALLDIR)Tools\\LLvm\\bin\\clang-cl.exe") {
        gn_args += clang_win=\"$$(VCINSTALLDIR)Tools\\LLvm\"
    } else:exists("C:\\Program Files\\LLVM\\bin\\clang-cl.exe") {
        gn_args += clang_win=\"C:\\Program Files\\LLVM\"
    }
}
# local msvc2019 environment, specific clang for skia.
msvc {
    CONFIG(detachClang){
        exists("C:\\Program Files\\LLVM\\bin\\clang-cl.exe") {
            gn_args += clang_win=\"C:\\Program Files\\LLVM\"
        } else:exists("$$(VCINSTALLDIR)Tools\\LLvm\\bin\\clang-cl.exe") {
            gn_args += clang_win=\"$$(VCINSTALLDIR)Tools\\LLvm\"
        }
    }
}
