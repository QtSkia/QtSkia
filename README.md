# QtSkia

[github原始仓库](https://github.com/QtSkia/QtSkia)

[gitee镜像](https://gitee.com/QtSkia/QtSkia)

## 简介

### Skia

Skia是一个开源的二维图形库，提供各种常用的API，并可在多种软硬件平台上运行。

谷歌Chrome浏览器、Chrome OS、安卓、火狐浏览器、火狐操作系统以及其它许多产品都使用它作为图形引擎。

Skia由谷歌出资管理，任何人都可基于BSD免费软件许可证使用Skia。

Skia开发团队致力于开发其核心部分， 并广泛采纳各方对于Skia的开源贡献。

* 源代码: skia.googlesource.com/skia.

* 提议: bug.skia.org.

* 论坛: skia-discuss@googlegroups.com.

* skia官网： https://skia.org

* 谷歌github镜像: https://github.com/google/skia.git

### QtSkia

QtSkia是在Qt框架中集成skia，实现的二维图形库。

QtSkia提供了QWidget、QOpenGLWidget、QQuickWindow、QQuickItem等常用Qt渲染组件与skia的对接，

可以方便地将skia引入到现有Qt项目中。

## CI徽章

占位，待修改。

| [Windows][win-link]| [Ubuntu][ubuntu-link]|[MacOS][macos-link]|[Android][android-link]|[IOS][ios-link]|
|---------------|---------------|-----------------|-----------------|----------------|
| ![win-badge]  | ![ubuntu-badge]      | ![macos-badge] |![android-badge]   |![ios-badge]   |


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

## HelloSkia示例

QtSkia处理了skia与QWidget、OpenGL、QQuick等渲染框架的融合问题，并将SkCanvas在接口中提供出来。

开发者只要重写父类虚函数，就能够使用SkCanvas了。

SkCanvas是一个类似于QPainter的画笔，但性能和功能都比QPainter强大许多。

下面示例QWidget中画线和写字的代码:

```c++
//main.cpp
#pragma once
#include <QApplication>
#include "QSkiaWidget.h"

class SkiaWidget : public QSkiaWidget {
    Q_OBJECT
public:
    void draw(SkCanvas *canvas) override
    {
        SkPaint p;
        p.setAntiAlias(true);
        p.setColor(SK_ColorRED);
        p.setStrokeWidth(2.0f);
        canvas->clear(SK_ColorWHITE);
        SkFont font;
        font.setSize(30);
        canvas->drawString("Hello Skia", 600, 300, font, p);
        canvas->drawLine(300, 300, 500, 500, p);
        canvas->flush();
    }
};

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    SkiaWidget win;
    win.resize(1024, 768);
    win.show();
    return app.exec();
}

```

效果如图：

![](doc/demo.png)

## 依赖环境

skia需要python2。(相关构建工具都是基于python2开发的。)

编译器需要支持C++11，skia推荐使用clang编译。

Qt版本5.9以上即可，无特殊限制。

建议使用5.9.x或5.12.x等长期支持版本。

### windows

编译器需要使用vs2017及以上。

官方强烈建议使用clang-cl。

注意32bit/x86架构,只能使用google提供的工具链，比较麻烦。

具体请参考skia官网：https://skia.org/user/build

### Linux

待补充

### MacOS

待补充

### Android

待补充

## 进度计划

|阶段|目标|进度|
|----|----|----|
|skia源码镜像|gitee|完成|
|依赖库源码镜像|gitee|完成|
|编译|-|-|
||改进Qt编译配置和工具链|持续进行中|
||Qt Windows平台编译skia|完成|
||Qt Linux平台编译skia|待测试|
||Qt MacOS平台编译skia|待测试|
|运行|-|-|
||简单画线|完成|
||简单文字|完成|
||贴图|计划中|
||Lottie绘制|计划中|
|Qt框架适配|||
||QOpenGLWidget|完成|
||QWidget Raster|完成|
||QOpenGLWindow|完成|
||QOuickWindow|完成|
||QQuickItem|计划中|
||QQuickFrameBuffer|计划中|
||QVulkanWindow|计划中|
|性能测试对比|-|计划中|

## 关于源码

skia官方仓库在 https://skia.googlesource.com/skia

github上面也有官方的镜像 https://github.com/google/skia

skia依赖的三方库有28个以上。

国内用户不一定能访问到googlesource，涛哥在github上整理了所有依赖仓库的镜像，

并使用自动化工具定期同步，具体见https://github.com/QtSkia

另外github速度不够快，所以涛哥在gitee上也做了镜像, 以方便国内用户，具体见：https://gitee.com/QtSkia
