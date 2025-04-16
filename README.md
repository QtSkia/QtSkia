[中文简体](README-zh.md)

# QtSkia

[github repo https://github.com/QtSkia/QtSkia](https://github.com/QtSkia/QtSkia)

[gitee mirror https://gitee.com/QtSkia/QtSkia](https://gitee.com/QtSkia/QtSkia)

# catalogue

- [QtSkia](#qtskia)
- [catalogue](#catalogue)
- [Introduction](#introduction)
  - [Skia](#skia)
  - [QtSkia](#qtskia-1)
- [CI Badge](#ci-badge)
- [Feature show](#feature-show)
  - [Shapes](#shapes)
  - [Bezier Curves](#bezier-curves)
  - [Translations and Rotations](#translations-and-rotations)
  - [Text Rendering](#text-rendering)
  - [Discrete Path Effects](#discrete-path-effects)
  - [Composed Path Effects](#composed-path-effects)
  - [Sum Path Effects](#sum-path-effects)
  - [Shaders](#shaders)
- [QtSkia use example](#qtskia-use-example)
- [Scheduled plan](#scheduled-plan)
- [Build](#build)
  - [dependency library](#dependency-library)
    - [windows](#windows)
    - [MacOS](#macos)
    - [Android](#android)
    - [Linux](#linux)
  - [code download](#code-download)
    - [skia and 3rdparty explain](#skia-and-3rdparty-explain)
  - [compile](#compile)
  - [Code struct](#code-struct)
- [Sponsor](#sponsor)



# Introduction

## Skia

Skia is an open source 2D graphics library which provides common APIs that work
across a variety of hardware and software platforms.  It serves as the graphics
engine for Google Chrome and Chrome OS, Android, Mozilla Firefox and Firefox
OS, and many other products.

Skia is sponsored and managed by Google, but is available for use by anyone
under the BSD Free Software License.  While engineering of the core components
is done by the Skia development team, we consider contributions from any
source.

  * Canonical source tree:
    [skia.googlesource.com/skia](https://skia.googlesource.com/skia).
  * Issue tracker:
    [bug.skia.org](https://bug.skia.org/).
  * Discussion forum:
    [skia-discuss@googlegroups.com](https://groups.google.com/forum/#!forum/skia-discuss).
  * API Reference and Overview: [skia.org/user/api](https://skia.org/user/api/).
  * Skia Fiddle: [fiddle.skia.org](https://fiddle.skia.org/c/@skcanvas_paint).

  * github mirror: https://github.com/google/skia.git

## QtSkia

QtSkia is an open source 2D graphics library which integration skia with qt's  render framework. 

QtSkia provide connection with QWidget、QOpenGLWidget、QQuickWindow、QQuickItem。

Qt developer can import skia to qt easily。

# CI Badge

| [Windows][win-link]|[MacOS][macos-link]| [Ubuntu][ubuntu-link]|[Android][android-link]|[IOS][ios-link]|
|---------------|---------------|-----------------|-----------------|----------------|
| ![win-badge]  |![macos-badge] | ![ubuntu-badge]      | ![android-badge]   |![ios-badge]   |

|[License][license-link]| [Release][release-link]|[Download][download-link]|[Issues][issues-link]|[Wiki][wiki-links]|
|-----------------|-----------------|-----------------|-----------------|-----------------|
|![license-badge] |![release-badge] | ![download-badge]|![issues-badge]|![wiki-badge]|

[win-link]: https://github.com/JaredTao/QtSkia/actions?query=workflow%3AWindows "WindowsAction"
[win-badge]: https://github.com/JaredTao/QtSkia/workflows/Windows/badge.svg  "Windows"

[ubuntu-link]: https://github.com/JaredTao/QtSkia/actions?query=workflow%3AUbuntu "UbuntuAction"
[ubuntu-badge]: https://github.com/JaredTao/QtSkia/workflows/Ubuntu/badge.svg "Ubuntu"

[macos-link]: https://github.com/JaredTao/QtSkia/actions?query=workflow%3AMacOS "MacOSAction"
[macos-badge]: https://github.com/JaredTao/QtSkia/workflows/MacOS/badge.svg "MacOS"

[android-link]: https://github.com/JaredTao/QtSkia/actions?query=workflow%3AAndroid "AndroidAction"
[android-badge]: https://github.com/JaredTao/QtSkia/workflows/Android/badge.svg "Android"

[ios-link]: https://github.com/JaredTao/QtSkia/actions?query=workflow%3AIOS "IOSAction"
[ios-badge]: https://github.com/JaredTao/QtSkia/workflows/IOS/badge.svg "IOS"

[release-link]: https://github.com/jaredtao/QtSkia/releases "Release status"
[release-badge]: https://img.shields.io/github/release/jaredtao/QtSkia.svg?style=flat-square "Release status"

[download-link]: https://github.com/jaredtao/QtSkia/releases/latest "Download status"
[download-badge]: https://img.shields.io/github/downloads/jaredtao/QtSkia/total.svg?style=flat-square "Download status"

[license-link]: https://github.com/jaredtao/QtSkia/blob/master/LICENSE "LICENSE"
[license-badge]: https://img.shields.io/badge/license-MIT-blue.svg "MIT"


[issues-link]: https://github.com/jaredtao/QtSkia/issues "Issues"
[issues-badge]: https://img.shields.io/badge/github-issues-red.svg?maxAge=60 "Issues"

[wiki-links]: https://github.com/jaredtao/QtSkia/wiki "wiki"
[wiki-badge]: https://img.shields.io/badge/github-wiki-181717.svg?maxAge=60 "wiki"
# Feature show

## Shapes
![](doc/feature/1.png)

## Bezier Curves
![](doc/feature/2.png)

## Translations and Rotations
![](doc/feature/3.png)

## Text Rendering

![](doc/feature/4.png)

## Discrete Path Effects
![](doc/feature/5.png)

## Composed Path Effects

![](doc/feature/6.png)

## Sum Path Effects

![](doc/feature/7.png)

## Shaders

![](doc/feature/8.png)

# QtSkia use example

[QtSkia us example](doc/Examples.md)


# Scheduled plan

* code mirror
- [x] skia code mirror
- [x] 3rdparth mirror
- [x] auto sync upstream code
- [x] local script for fetch code

* Compile and ci
- [x] specific compile flow with qmake
- [x] Windows platform compile.
- [x] MacOS compile
- [ ] Linux compile
- [ ] Android

* effect
- [x] sample text,line
- [X] Skia inner effect
- [ ] texture
- [ ] Lottie

* Qt Framework adapted

1. Gui 
- [x] QOpenGLWindow
- [ ] QWindow
- [ ] QVulkanWindow

2. Widget
- [x] QWidget CPURaster
- [x] QOpenGLWidget

3. Quick
- [x] QOuickWindow
- [X] QQuickItem
- [ ] QQuickFrameBuffer

4. Qt6 RHI

- [ ] under construction

* performance test
  
- [ ] under construction

# Build

## dependency library

python 2

Qt 5.12.x 64-bit

Note:32bit/x86 arch, need the toolchain by google， QtSkia not suooprt，detail info can be found in: https://skia.org/user/build

### windows

Compiler need visual studio 2017 and later, clang-cl is better.

### MacOS

under construction

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

## Code struct

|directory|descript|
|:-----------:|:-------------:|
|3rdparty|skia and depency library|
|doc| document |
|examples| examples|
|QtSkia|QtSkia|
|skiaBuild|Qt qmake compile skia |


# Sponsor

If you feel the share content is good, treat the author a drink.

<img src="https://gitee.com/jaredtao/jaredtao/raw/master/img/weixin.jpg?raw=true" width="25%" height="25%" /><img src="https://gitee.com/jaredtao/jaredtao/raw/master/img/zhifubao.jpg?raw=true" width="25%" height="25%" />

it's WeChat Pay and Alipay
