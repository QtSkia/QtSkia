#pragma once
#include "QSkiaWidget.h"
#include "SampleRender.h"
class SkiaWidget : public QSkiaWidget {
    Q_OBJECT
public:
    virtual void draw(SkCanvas* canvas, int elapsed) override
    {
        m_renderer.draw(canvas, elapsed, this->width(), this->height());
    }

private:
    SampleRender m_renderer;
};
