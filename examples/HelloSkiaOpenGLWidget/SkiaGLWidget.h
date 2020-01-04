#pragma once
#include "QSkiaOpenGLWidget.h"
#include "SampleRender.h"
class SkiaGLWidget : public QSkiaOpenGLWidget {
    Q_OBJECT
public:
    virtual void draw(SkCanvas* canvas, int elapsed = 16) override
    {
        m_renderer.draw(canvas, elapsed, this->width(), this->height());
    }

private:
    SampleRender m_renderer;
};
