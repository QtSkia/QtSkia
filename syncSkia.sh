#!/bin/sh -e
if [ ! -d "3rdparty/skia" ]; then
    git clone "https://github.com/QtSkia/skia.git" --no-checkout --depth 1 3rdparty/skia
fi
pushd 3rdparty/skia
git pull --depth=1 "https://github.com/QtSkia/skia" --allow-unrelated-histories
export GIT_SYNC_DEPS_PATH=$PWD/DEPS-github
python tools/git-sync-deps -v
popd
