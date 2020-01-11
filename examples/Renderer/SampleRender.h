#pragma once
#include "IRender.h"
#include "core/SkFont.h"
#include "core/SkPaint.h"
#include "core/SkCanvas.h"

class SampleRender : public IRender{
public:
    SampleRender();
    void draw(SkCanvas *canvas, int elapsed, int w, int h) override;
private:
    SkPaint m_paint;
    SkFont m_font;
    float m_rotateSpeed = 90.0f / 1000;
    int m_rotateAngle = 0;
};
