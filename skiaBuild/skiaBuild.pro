TEMPLATE = aux

include($$PWD/buildTool/buildTool.pri)
include($$PWD/buildConfig/buildConfig.pri)
include($$PWD/../uniqueDestdir.pri)
DESTDIR = $$destPath

SKIA_SRC_PATH=$$system_quote($$system_path($$absolute_path($$PWD/../3rdparty/skia)))
SKIA_OUT_PATH=$$system_quote($$DESTDIR)

build_pass|!debug_and_release {
    GN_ARGS = $$system_quote($$gn_args)
    GN_RUN =$$GN gen $$SKIA_OUT_PATH --args=$$GN_ARGS --root=$$SKIA_SRC_PATH $$verbose_flags
    message("gn: $$GN_RUN " )
    !system($$GN_RUN): {
        error ("gn run error")
    }
    runninja.target = run_ninja
    numOfProcessor=$$(NUMBER_OF_PROCESSORS)
    greaterThan(numOfProcessor, 1) {
        runninja.commands = $$NINJA -C $$system_quote($$system_path($$SKIA_OUT_PATH)) -j $$numOfProcessor $$verbose_flags
    } else {
        runninja.commands = $$NINJA -C $$system_quote($$system_path($$SKIA_OUT_PATH)) $$verbose_flags
    }
    message("ninja: $$runninja.commands ")
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
