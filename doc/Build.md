# Build

## dependency library

python 2

Qt 5.12.x 64-bit

Note:32bit/x86 arch, need the toolchain by google， QtSkia not suooprt，detail info can be found in: https://skia.org/user/build

### windows

Compiler need vs2017 and about, clang-cl is better.

### MacOS

XCode. 

### Android

under construction

### Linux

under construction

## code download

1. Downlaod QtSkia

```shell
git clone https://github.com/QtSkia/QtSkia.git
```

China user can use gitee mirror for speed up.

```shell
git clone https://gitee.com/QtSkia/QtSkia.git
```

2. Download skia and 3rdparty

run script 'syncSkia' at root directory of QtSkia.

China user can use syncSkia-gitee replace for speed up from gitee mirror.

Windows platform click run syncSkia.bat， or termianl run：

```bat
cd QtSkia
syncSkia.bat
```

MacOS or linux platform, termianl run：
```shell
cd QtSkia
chmod a+x syncSkia.sh
./syncSkia.sh
```

### skia and 3rdparty explain

skia origin site: https://skia.googlesource.com/skia

github mirror: https://github.com/google/skia

skia depend on many thrid library. (about 28+)

QtSkia provite mirror on github、gitee, detail on：

https://github.com/QtSkia

https://gitee.com/QtSkia


QtSkia use script auto sync these code from upstream on timer。

QtSkia not edit there code，just add github、gitee mirror support and compiler support.

## compile

use QtCreator import QtSkia.pro

or run qt commandline:
```shell
qmake 
make
```

# Deployment

1. normal Qt Deployemnt step. windeployqt or macdeployqt

2. add QtSkia and skia.

example FeatureShow on windows: add QtSkiaQuick.dll and skia.dll.

release mode：

file 'skia.dll' size 7.16 MB. 

file 'QtSkiaQuick.dll' size 54 KB.

![](dep.png)