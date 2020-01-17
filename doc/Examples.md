# QtSkia use case

QtSkia deal with the fusion of skia and Qt render framework such as QWidget、QOpenGLWindow、QQuickWindow、QQuickItem ，and export SkCanvas in the interface.

As long as inherit the parent class and override virtual-function，developer can draw anything in Qt with SkCanvas.


## QWidget use skia

inherit QSkiaWidget class and rewrite draw function

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

effects：

![](demo.png)

## QWidget OpenGL use skia

inherit QSkiaOpenGLWidget class and rewrite draw function

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
## Pure OpenGL window + skia

QSkiaOpenGLWindow just depend on QtGUI module and everying can be render by OpenGL。

Here is a demo for draw star effect path.

```C++
#pragma once
#include "QSkiaOpenGLWindow.h"
#include "core/SkCanvas.h"
#include "core/SkPaint.h"
#include "effects/SkDashPathEffect.h"
#include "effects/SkDiscretePathEffect.h"

//generate star effect path.
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
effect:

![](opengl.png)

## QtQuickWindow use skia

inherit QSkiaQuickWindow，developer can draw anything in Qml Window.

```C++
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

class SkiaQuickWindow : public QSkiaQuickWindow {
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

    virtual void drawBeforeSG(SkCanvas* canvas, int elapsed) override
    {
        int w = this->width();
        int h = this->height();
        m_rotateAngle = int(elapsed * m_rotateSpeed + m_rotateAngle) % 360;

        SkPaint p;
        p.setAntiAlias(true);
        p.setColor(SK_ColorRED);
        p.setStrokeWidth(2.0f);
        SkFont font;
        font.setSize(30);
        canvas->clear(SK_ColorWHITE);

        canvas->rotate(m_rotateAngle, w / 2, h / 2);
        canvas->drawString("Hello Skia", w / 2 - 20, h / 2, font, p);
        canvas->drawLine(w * 0.2f, h * 0.2f, w * 0.4f, h * 0.4f, p);

        canvas->flush();
    }
    virtual void drawAfterSG(SkCanvas* canvas, int elapsed) override
    {
        //don't clear here.
        int w = this->width();
        int h = this->height();
        canvas->rotate(m_rotateAngle, w / 2, h / 2);
        canvas->drawPath(m_path, m_paint);
        canvas->flush();
    }

private:
    SkPaint m_paint;
    SkPath m_path;
    sk_sp<SkPathEffect> m_effect = nullptr;
    float m_rotateSpeed = 90.0f / 1000;
    int m_rotateAngle = 0;
};

```

effects:

![](QSkiaQuickWindow.gif)

the text and red line is rendered before SceneGraph, star path is after.

## QtQuickItem use skia

inherit QSkiaQuickItem, developer can draw in Qml Item.

```C++
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

class SkiaQuickItem : public QSkiaQuickItem {
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

        m_starPaint.setPathEffect(m_effect);
        m_starPaint.setStyle(SkPaint::kStroke_Style);
        m_starPaint.setStrokeWidth(2.0f);
        m_starPaint.setAntiAlias(true);
        m_starPaint.setColor(0xff4285F4);

        m_linePaint.setAntiAlias(true);
        m_linePaint.setStrokeWidth(2.0f);
        m_linePaint.setColor(SK_ColorRED);

        m_font.setSize(30);
    }
    virtual void onResize(int w, int h) override {}
    virtual void draw(SkCanvas* canvas, int elapsed) override
    {
        auto size = this->size().toSize();
        int w = size.width();
        int h = size.height();
        m_rotateAngle = int(elapsed * m_rotateSpeed + m_rotateAngle) % 360;

        canvas->clear(SK_ColorWHITE);
        canvas->drawPath(m_path, m_starPaint);

        canvas->drawString("Hello Skia", w / 2 - 20, h / 2, m_font, m_linePaint);
        canvas->drawLine(10, 10, w, h, m_linePaint);
        canvas->flush();
    }
private:
    SkPaint m_starPaint;
    SkPaint m_linePaint;
    SkFont m_font;
    SkPath m_path;
    sk_sp<SkPathEffect> m_effect = nullptr;
    float m_rotateSpeed = 90.0f / 1000;
    int m_rotateAngle = 0;
};

```

register item to qml

```C++
    qmlRegisterType<SkiaQuickItem>("SkiaQuickItem", 1, 0, "SkiaQuickItem");
```

Qml like this:

```Qml
import QtQuick 2.0
import QtQuick.Controls 2.0
import SkiaQuickItem 1.0
Rectangle {
    width: 800
    height: 600
    color: "lightgray"
    SkiaQuickItem {
        id: renderer
        width: 600
        height: 400
        anchors.centerIn: parent
        Rectangle {
            width: 100
            height: 100
            anchors.centerIn: parent
            color: "red"
        }
        transform: [
            Rotation { id: rotation; axis.x: 0; axis.z: 0; axis.y: 1; angle: 0; origin.x: renderer.width / 2; origin.y: renderer.height / 2; },
            Translate { id: txOut; x: -renderer.width / 2; y: -renderer.height / 2 },
            Scale { id: scale; },
            Translate { id: txIn; x: renderer.width / 2; y: renderer.height / 2 }
        ]
    }
    SequentialAnimation {
        ParallelAnimation {
            NumberAnimation { target: scale; property: "xScale"; to: 0.6; duration: 1000; easing.type: Easing.InOutBack }
            NumberAnimation { target: scale; property: "yScale"; to: 0.6; duration: 1000; easing.type: Easing.InOutBack }
        }
        NumberAnimation { target: rotation; property: "angle"; to: 80; duration: 1000; easing.type: Easing.InOutCubic }
        NumberAnimation { target: rotation; property: "angle"; to: -80; duration: 1000; easing.type: Easing.InOutCubic }
        NumberAnimation { target: rotation; property: "angle"; to: 0; duration: 1000; easing.type: Easing.InOutCubic }
        NumberAnimation { target: renderer; property: "opacity"; to: 0.1; duration: 1000; easing.type: Easing.InOutCubic }
        PauseAnimation { duration: 1000 }
        NumberAnimation { target: renderer; property: "opacity"; to: 1.0; duration: 1000; easing.type: Easing.InOutCubic }
        ParallelAnimation {
            NumberAnimation { target: scale; property: "xScale"; to: 1; duration: 1000; easing.type: Easing.InOutBack }
            NumberAnimation { target: scale; property: "yScale"; to: 1; duration: 1000; easing.type: Easing.InOutBack }
        }
        running: true
        loops: Animation.Infinite
    }
}
```
effects: 

![](QQuickItem.gif)