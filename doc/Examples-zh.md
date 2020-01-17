# QtSkia使用示例

QtSkia处理了skia与QWidget、QOpenGLWindow、QQuick等渲染框架的融合问题，并将SkCanvas在接口中提供出来。

开发者只要重写父类虚函数，使用SkCanvas执行绘制操作即可。

SkCanvas是一个类似于QPainter的画笔，但性能和功能都比QPainter强大许多。

## QWidget使用skia

继承QSkiaWidget类并重写draw函数即可。

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

        SkFont font;
        font.setSize(30);

        canvas->clear(SK_ColorWHITE);

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

![](demo.png)

## QWidget 使用 OpenGL skia

QWidget本身是CPU光栅化渲染的，适合在一些无GPU的设备中运行。

如果设备支持OpenGL，也可以在QWidget中集成OpenGL, 实现GPU硬件加速。

只要继承QSkiaOpenGLWidget类即可：

```C++
class SkiaGLWidget : public QSkiaOpenGLWidget {
    Q_OBJECT
public:
    void draw(SkCanvas *canvas) override
    {
        SkPaint p;
        p.setAntiAlias(true);
        p.setColor(SK_ColorRED);
        p.setStrokeWidth(2.0f);

        SkFont font;
        font.setSize(30);

        canvas->clear(SK_ColorWHITE);

        canvas->drawString("Hello Skia", 600, 300, font, p);
        canvas->drawLine(300, 300, 500, 500, p);

        canvas->flush();
    }
};
```
## 纯OpenGL窗口 + skia

QtSkia还提供了纯粹的OpenGL窗口，仅依赖Qt GUI模块，可以实现全部UI由OpenGL渲染。

下面代码示例, 在纯OpenGL窗口中，绘制星形路径特效

```C++
#pragma once
#include "QSkiaOpenGLWindow.h"
#include "core/SkCanvas.h"
#include "core/SkPaint.h"
#include "effects/SkDashPathEffect.h"
#include "effects/SkDiscretePathEffect.h"

//生成星形路径
static SkPath star()
{
    const SkScalar R = 115.2f, C = 128.0f;
    SkPath path;
    path.moveTo(C + R, C);
    for (int i = 1; i < 8; ++i) {
        SkScalar a = 2.6927937f * i;
        path.lineTo(C + R * cos(a), C + R * sin(a));
    }
    return path;
}
class SkiaGLWindow : public QSkiaOpenGLWindow {
    Q_OBJECT
public:
    virtual void onInit(int w, int h) override
    {
        const SkScalar intervals[] = { 10.0f, 5.0f, 2.0f, 5.0f };
        size_t count = sizeof(intervals) / sizeof(intervals[0]);
        m_effect = SkPathEffect::MakeCompose(
            SkDashPathEffect::Make(intervals, count, 0.0f),
            SkDiscretePathEffect::Make(10.0f, 4.0f));
        m_path = star();

        m_paint.setPathEffect(m_effect);
        m_paint.setStyle(SkPaint::kStroke_Style);
        m_paint.setStrokeWidth(2.0f);
        m_paint.setAntiAlias(true);
        m_paint.setColor(0xff4285F4);
    }
    virtual void onResize(int w, int h) override {}
    virtual void draw(SkCanvas* canvas, int elapsed) override
    {
        canvas->clear(SK_ColorWHITE);

        canvas->drawPath(m_path, m_paint);

        canvas->flush();
    }

private:
    SkPaint m_paint;
    SkPath m_path;
    sk_sp<SkPathEffect> m_effect = nullptr;
};

```
效果如下:

![](opengl.png)

## QtQuick/Qml使用skia

QtSkia为QtQuick/Qml程序也提供了skia支持。

继承QSkiaQuickWindow类，可以在整个Qml窗口的渲染流程中加入skia渲染。

继承QSkiaQuickItem类，可以在任意Item中使用skia。