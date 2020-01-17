#pragma once
#include "QSkiaQuickItem.h"

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
