#pragma once
#include "QSkiaQuickWindow.h"

#include "ComposeRender.h"
#include "core/SkCanvas.h"
#include "core/SkFont.h"
#include "core/SkPaint.h"
#include "effects/SkDashPathEffect.h"
#include "effects/SkDiscretePathEffect.h"
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
    virtual void onUninit() override
    {
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
