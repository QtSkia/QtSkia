isEmpty(uniqueDestdir) {
    uniqueDestdir=1
    basePath=$$PWD/bin
    compilerPath=gcc
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
    if($$QtSkia_Static_Build) {
        libPath=static
    } else {
        libPath=shared
    }
    CONFIG(debug, debug|release) {
        modePath=debug
    } else {
        modePath=release
    }
    destPath=$${basePath}/$${compilerPath}/$${libPath}/$${modePath}
    message(destPath $$destPath)
}
