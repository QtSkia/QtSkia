gn_args = is_official_build=false
CONFIG(debug, debug|release) {
    gn_args += \
        is_debug=true
} else {
    gn_args += \
        is_debug=false
}
if($$QtSkia_Static_Build) {
    gn_args += \
        is_component_build=false
} else {
    gn_args += \
        is_component_build=true
}

gn_args += \
    win_vc=\"$$clean_path($$(VCINSTALLDIR))\" \
    win_toolchain_version=\"$$(VCToolsVersion)\" \
    win_sdk_version=\"$$clean_path($$(WindowsSDKVersion))\"

clang_cl {
    exists("$$(VCINSTALLDIR)Tools\\LLvm\\bin\\clang-cl.exe") {
        gn_args += clang_win=\"$$(VCINSTALLDIR)Tools\\LLvm\"
    } else:exists("C:\\Program Files\\LLVM\\bin\\clang-cl.exe") {
        gn_args += clang_win=\"C:\\Program Files\\LLVM\"
    }
}
# local msvc2019 environment, specific clang for skia.
CONFIG(detectClang){
    exists("C:\\Program Files\\LLVM\\bin\\clang-cl.exe") {
        gn_args += clang_win=\"C:\\Program Files\\LLVM\"
    } else:exists("$$(VCINSTALLDIR)Tools\\LLvm\\bin\\clang-cl.exe") {
        gn_args += clang_win=\"$$(VCINSTALLDIR)Tools\\LLvm\"
    }
}
