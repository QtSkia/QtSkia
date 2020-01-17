#include "SampleRender.h"

SampleRender::SampleRender()
{
}

void SampleRender::draw(SkCanvas* canvas, int elapsed, int w, int h)
{
    m_rotateAngle = int(elapsed * m_rotateSpeed + m_rotateAngle) % 360;

    canvas->clear(SK_ColorWHITE);
    canvas->rotate(m_rotateAngle, w / 2, h / 2);
    canvas->drawString("Hello Skia", w / 2 - 20, h / 2, m_font, m_paint);
    canvas->drawLine(w * 0.2f, h * 0.2f, w * 0.4f, h * 0.4f, m_paint);
    canvas->flush();
}

void SampleRender::init(int w, int h)
{
    m_paint.setAntiAlias(true);
    m_paint.setColor(SK_ColorRED);
    m_paint.setStrokeWidth(2.0f);
    m_font.setSize(30);
}

void SampleRender::resize(int w, int h)
{
}
