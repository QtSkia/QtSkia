#!/bin/sh -e
if [ ! -d "3rdparty/skia" ]; then
    git clone "https://github.com/QtSkia/skia.git" --branch QtSkia --depth 1 3rdparty/skia
    pushd 3rdparty/skia
else
    pushd 3rdparty/skia
    git pull --depth=1 "https://github.com/QtSkia/skia.git" QtSkia --allow-unrelated-histories
fi
export GIT_SYNC_DEPS_PATH=$PWD/DEPS-github
python tools/git-sync-deps -v
popd
