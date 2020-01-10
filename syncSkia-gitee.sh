#!/bin/bash
git submodule update --init --reference https://gitee.com/QtSkia/skia.git --depth 1 3rdparty/skia
cd 3rdparty/skia
set GIT_SYNC_DEPS_PATH=$PWD/DEPS-gitee
python tools/git-sync-deps -v

