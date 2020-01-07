basePath=$$PWD/bin
msvc:clang_cl {
    compilerPath=clang
} else:msvc {
    compilerPath=/msvc
}

CONFIG(debug, debug|release) {
    modePath=debug
} else {
    modePath=release
}
destPath=$${basePath}/$${compilerPath}/$${modePath}
#message(destPath $$destPath)

