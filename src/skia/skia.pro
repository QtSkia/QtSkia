TEMPLATE = aux

DESTDIR = $$absolute_path($$PWD/../../bin)

include($$PWD/buildTool/buildTool.pri)

CONFIG +=precompile_header

linux: include($$PWD/config/linux.pri)
macos: include($$PWD/config/mac_osx.pri)
win32: include($$PWD/config/windows.pri)
isEmpty(gn_args): error(No gn_args found please make sure you have valid configuration.)


SKIA_SRC_PATH=$$system_path($$absolute_path($$PWD/../3rdparty/skia))
SKIA_OUT_PATH=$$system_path($$absolute_path($${DESTDIR}/skia))

build_pass|!debug_and_release {
    # update python skia/tools/git-sync-deps
    sync_deps=python $$system_path($${SKIA_SRC_PATH}/tools/git-sync-deps)
    message("Running: $$sync_deps ")
    if(!system($$sync_deps)) {
        error ("sync deps error")
    }

#    gn_args = $$system_quote(is_debug=false is_component_build=true current_cpu=4)
    args = $$system_quote(is_debug=false is_component_build=true)
    gn_run = cd $$system_quote($$SKIA_SRC_PATH) && $$GN gen $$system_quote($$SKIA_OUT_PATH) --root=$$system_quote($$SKIA_SRC_PATH)
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
