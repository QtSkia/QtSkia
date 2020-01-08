#pragma once
#include "QSkiaQuickItem.h"
#include "SampleRender.h"
class SkiaQuickItem : public QSkiaQuickItem {
    Q_OBJECT
public:
    SkiaQuickItem(QQuickItem* parent = nullptr)
        : QSkiaQuickItem(parent)
    {
    }
    virtual void draw(SkCanvas* canvas, int elapsed) override
    {
        m_renderer.draw(canvas, elapsed, static_cast<int>(width()), static_cast<int>(height()));
    }

private:
    SampleRender m_renderer;
};
