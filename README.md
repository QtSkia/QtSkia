# QtSkia

[gitee镜像](https://gitee.com/QtSkia/QtSkia)

## 简介

### Skia

Skia是一个开源的二维图形库，提供各种常用的API，并可在多种软硬件平台上运行。

谷歌Chrome浏览器、Chrome OS、安卓、火狐浏览器、火狐操作系统以及其它许多产品都使用它作为图形引擎。

Skia由谷歌出资管理，任何人都可基于BSD免费软件许可证使用Skia。

Skia开发团队致力于开发其核心部分， 并广泛采纳各方对于Skia的开源贡献。

源代码: skia.googlesource.com/skia.

提议: bug.skia.org.

论坛: skia-discuss@googlegroups.com.

### QtSkia

QtSkia是在Qt框架中集成skia，实现的二维图形库。

QtSkia提供了QWidget、QOpenGLWidget、QQuickWindow、QQuickItem等常用Qt渲染组件与skia的对接，

可以方便地将skia引入到现有Qt项目中。

在QtSkia中, 通常使用SkCanvas实现二维图形的渲染。

SkCanvas是一个类似于QPainter的画笔，但比QPainter强大许多。

下面示例画线和写字的代码:

```c++
void draw(SkCanvas *canvas)
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
```

效果如图：

![](doc/demo.png)

## CI徽章
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
||QOpenGLWindow|计划中|
||QQuickItem|计划中|
||QQuickFrameBuffer|计划中|
||QVulkanWindow|计划中|
|性能测试对比|-|计划中|

## 关于源码

skia官方仓库在 https://skia.googlesource.com/skia

github上面也有镜像 https://github.com/google/skia

国内用户不一定能访问到googlesource，github速度也不快，所以我个人在gitee上做了一个镜像。

另外skia依赖的三方库有28个以上，源码也在gitee上做了镜像，不定期更新，具体可以关注: https://gitee.com/QtSkia



