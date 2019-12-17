TEMPLATE = aux

DESTDIR = $$absolute_path($$PWD/../../bin)

include($$PWD/buildTool/buildTool.pri)

#skia_qt_path=$$getenv(QTDIR)
#message(skia_qt_path $${skia_qt_path})

CONFIG(debug, debug|release) {
    gn_args = $$system_quote(is_debug=true is_official_build=false is_component_build=true win_toolchain_version=\"14.16.27023\")
#    gn_args = $$system_quote(is_debug=true is_official_build=false is_component_build=true clang_win=\"C:\\Program Files\\LLVM\")

    verbose_flags = -v
} else {
    #gn_args = $$system_quote(is_debug=false is_official_build=false is_component_build=true clang_win=\"C:\\Program Files\\LLVM\")
    gn_args = $$system_quote(is_debug=false is_official_build=false is_component_build=true win_toolchain_version=\"14.16.27023\")
    verbose_flags =
}


SKIA_SRC_PATH=$$system_path($$absolute_path($$PWD/../3rdparty/skia))
SKIA_OUT_PATH=$$system_path($$absolute_path($${SKIA_SRC_PATH}/out/Shared))

build_pass|!debug_and_release {
    # update python skia/tools/git-sync-deps
    sync_deps=python $$verbose_flags $$system_path($${SKIA_SRC_PATH}/tools/git-sync-deps)
    message("Running: $$sync_deps ")
    if(!system($$sync_deps)) {
        error ("sync deps error")
    }
    gn_run =$$GN gen $$system_quote($$SKIA_OUT_PATH) --root=$$system_quote($$SKIA_SRC_PATH) --args=$$system_quote($$gn_args) $$verbose_flags
    message("Running: $$gn_run " )
    if(!system($$gn_run)) {
        error ("gn run error")
    }
    runninja.target = run_ninja
    runninja.commands = $$NINJA -C $$system_quote($$system_path($$SKIA_OUT_PATH))
    message("when build ninja: $$runninja.commands " )
    QMAKE_EXTRA_TARGETS += runninja


    build_pass:build_all: default_target.target = all
    else: default_target.target = first
    default_target.depends = runninja
    QMAKE_EXTRA_TARGETS += default_target
}

!build_pass:debug_and_release {
    # Special GNU make target for the meta Makefile that ensures that our debug and release Makefiles won't both run ninja in parallel.
    notParallel.target = .NOTPARALLEL
    QMAKE_EXTRA_TARGETS += notParallel
}
