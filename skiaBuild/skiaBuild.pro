TEMPLATE = aux

include($$PWD/buildTool/buildTool.pri)
include($$PWD/../uniqueDestdir.pri)
DESTDIR = $$destPath

SKIA_SRC_PATH=$$system_quote($$system_path($$absolute_path($$PWD/../3rdparty/skia)))
SKIA_OUT_PATH=$$system_quote($$DESTDIR)

build_pass|!debug_and_release {
    # update python skia/tools/git-sync-deps
    github_sync=\"set GIT_SYNC_DEPS_PATH=$$absolute_path($$SKIA_SRC_PATH/DEPS-github)\"
    gitee_sync=\"set GIT_SYNC_DEPS_PATH=$$absolute_path($$SKIA_SRC_PATH/DEPS-gitee)\"
    git_sync=\"echo 0\"

    if ($$QtSkia_Use_Gitee) {
        git_sync = $$gitee_sync
    } else {
        git_sync = $$github_sync
    }
    message("git sync:" $$git_sync)
    sync_deps=python $$verbose_flags $$absolute_path($${SKIA_SRC_PATH}/tools/git-sync-deps)
    message("Running: $$sync_deps ")
    if(!system($$git_sync && $$sync_deps)) {
        error ("sync deps error")
    }
    GN_ARGS = $$system_quote($$gn_args)
    GN_RUN =$$GN gen $$SKIA_OUT_PATH --args=$$GN_ARGS --root=$$SKIA_SRC_PATH $$verbose_flags
    message("Running: $$GN_RUN " )
    !system($$GN_RUN): {
        error ("gn run error")
    }
    runninja.target = run_ninja
    greaterThan(Max_Parallel, 1) {
        runninja.commands = $$NINJA -C $$system_quote($$system_path($$SKIA_OUT_PATH)) -j $$Max_Parallel
    } else {
        runninja.commands = $$NINJA -C $$system_quote($$system_path($$SKIA_OUT_PATH))
    }
    message(Max_Parallel $$Max_Parallel)
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
