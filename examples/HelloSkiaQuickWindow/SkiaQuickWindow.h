#pragma once
#include "QSkiaQuickWindow.h"
#include "SampleRender.h"
#include "ComposeRender.h"
class SkiaQuickWindow : public QSkiaQuickWindow {
    Q_OBJECT
public:
    virtual void drawBeforeSG(SkCanvas* canvas, int elapsed) override
    {
        m_renderer.draw(canvas, elapsed, this->width(), this->height());
    }
    virtual void drawAfterSG(SkCanvas* canvas, int elapsed) override
    {
        m_composeRender.draw(canvas, elapsed, this->width(), this->height());
    }

private:
    SampleRender m_renderer;
    ComposeRender m_composeRender;
};
