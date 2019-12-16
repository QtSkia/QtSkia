TEMPLATE = aux

DESTDIR = $$PWD/../bin

include(../buildTool/buildTool.pri)

SKIA_SRC_PATH=$$PWD/3rdparty/skia
SKIA_OUT_PATH=$${OUT_PWD}/skia
# update python skia/tools/git-sync-deps
system(python $$system_path($${SKIA_SRC_PATH}/tools/git-sync-deps))

build_pass|!debug_and_release {
    gn_args = $$system_quote(is_debug=false id_component_build=true)
    gn_run = $$GN gen $$SKIA_OUT_PATH --args=$$gn_args
    message("Running: $$gn_run " )
    if(!system($$gn_run)) {
        error ("gn run error")
    }
    runninja.target = run_ninja
    runninja.commands = $$NINJA -C $$SKIA_OUT_PATH
    QMAKE_EXTRA_TARGETS += runninja
}

!build_pass:debug_and_release {
    # Special GNU make target for the meta Makefile that ensures that our debug and release Makefiles won't both run ninja in parallel.
    notParallel.target = .NOTPARALLEL
    QMAKE_EXTRA_TARGETS += notParallel
}
