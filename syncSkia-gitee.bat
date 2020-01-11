@echo off
git clone https://gitee.com/QtSkia/skia.git --depth 1 3rdparty/skia
cd 3rdparty/skia
git pull --depth=1 https://gitee.com/QtSkia/skia.git
set GIT_SYNC_DEPS_PATH=%cd%/DEPS-gitee
python tools/git-sync-deps -v
cd ../..
