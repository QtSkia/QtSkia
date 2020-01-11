#!/bin/sh -e
git submodule update --init --depth 1 3rdparty/skia
cd 3rdparty/skia
export GIT_SYNC_DEPS_PATH=$PWD/DEPS-github
python tools/git-sync-deps -v
cd ../..
