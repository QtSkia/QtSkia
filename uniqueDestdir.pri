basePath=$$PWD/bin
msvc:clang_cl {
    compilerPath=clang
} else:msvc {
    compilerPath=msvc
}
macos|ios {
    compilerPath=clang
}
linux|android {
    compilerPath=gcc
}
CONFIG(debug, debug|release) {
    modePath=debug
} else {
    modePath=release
}
destPath=$${basePath}/$${compilerPath}/$${modePath}
#message(destPath $$destPath)

