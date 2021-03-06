#pragma once
#include "IRender.h"
#include "core/SkCanvas.h"
#include "core/SkPaint.h"
#include "core/SkRect.h"
#include "core/SkRRect.h"
class ShapesRender : public IRender
{
public:
    void draw(SkCanvas *canvas, int elapsed, int w, int h) override;
    void init(int w, int h) override;
    void resize(int w, int h) override;
private:
};

