#!/bin/sh -e
git clone "https://gitee.com/QtSkia/skia.git" --no-checkout --depth 1 3rdparty/skia
pushd 3rdparty/skia
git pull --depth=1 "https://gitee.com/QtSkia/skia"
export GIT_SYNC_DEPS_PATH=$PWD/DEPS-gitee
python tools/git-sync-deps -v
popd
