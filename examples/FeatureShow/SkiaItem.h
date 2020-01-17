#pragma once
#include "QSkiaQuickItem.h"

#include "BezierRender.h"
#include "ComposeRender.h"
#include "DiscretePathRender.h"
#include "RotationsRender.h"
#include "ShaderRender.h"
#include "ShapesRender.h"
#include "SumPathRender.h"
#include "TextRender.h"
template <class Render>
class SkiaItem : public QSkiaQuickItem {
public:
    virtual void onInit(int w, int h) override
    {
        m_render.init(w, h);
    }
    virtual void onResize(int w, int h) override
    {
        m_render.resize(w, h);
    }
    virtual void draw(SkCanvas* canvas, int elapsed) override
    {
        m_render.draw(canvas, elapsed, width(), height());
    }

private:
    Render m_render;
};
using SkiaShapeItem = SkiaItem<ShapesRender>;
using SkiaBezierItem = SkiaItem<BezierRender>;
using SkiaRotationItem = SkiaItem<RotationsRender>;
using SkiaTextItem = SkiaItem<TextRender>;
using SkiaDiscreteItem = SkiaItem<DiscretePathRender>;
using SkiaComposeItem = SkiaItem<ComposeRender>;
using SkiaSumPathItem = SkiaItem<SumPathRender>;
using SkiaShaderItem = SkiaItem<ShaderRender>;
static void registerSkiaItem ()
{
    qmlRegisterType<SkiaShapeItem>("SkiaItem", 1, 0, "SkiaShapeItem");
    qmlRegisterType<SkiaBezierItem>("SkiaItem", 1, 0, "SkiaBezierItem");
    qmlRegisterType<SkiaRotationItem>("SkiaItem", 1, 0, "SkiaRotationItem");
    qmlRegisterType<SkiaTextItem>("SkiaItem", 1, 0, "SkiaTextItem");
    qmlRegisterType<SkiaDiscreteItem>("SkiaItem", 1, 0, "SkiaDiscreteItem");
    qmlRegisterType<SkiaComposeItem>("SkiaItem", 1, 0, "SkiaComposeItem");
    qmlRegisterType<SkiaSumPathItem>("SkiaItem", 1, 0, "SkiaSumPathItem");
    qmlRegisterType<SkiaShaderItem>("SkiaItem", 1, 0, "SkiaShaderItem");
}

