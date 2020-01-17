#pragma once

#include "IRender.h"
#include "core/SkCanvas.h"
#include "core/SkPaint.h"
#include "core/SkPath.h"

class ShaderRender : public IRender
{
public:
    void draw(SkCanvas *canvas, int elapsed, int w, int h) override;
    void init(int w, int h) override;
    void resize(int w, int h) override;
private:
    SkPaint paint;
    SkPath path;
};

