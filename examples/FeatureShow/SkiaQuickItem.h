#pragma once
#include "QSkiaQuickItem.h"

#include "ComposeRender.h"
#include "core/SkCanvas.h"
#include "core/SkFont.h"
#include "core/SkPaint.h"
#include "effects/SkDashPathEffect.h"
#include "effects/SkDiscretePathEffect.h"

class SkiaQuickItem : public QSkiaQuickItem {
    Q_OBJECT
public:
    virtual void onInit(int w, int h) override
    {

    }
    virtual void onResize(int w, int h) override {}
    virtual void draw(SkCanvas* canvas, int elapsed) override
    {
        auto size = this->size().toSize();
        int w = size.width();
        int h = size.height();
        m_rotateAngle = int(elapsed * m_rotateSpeed + m_rotateAngle) % 360;


    }
private:

    float m_rotateSpeed = 90.0f / 1000;
    int m_rotateAngle = 0;
};
