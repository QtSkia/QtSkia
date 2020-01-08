#include "SampleRender.h"
#include "core/SkFont.h"
#include "core/SkCanvas.h"
#include "core/SkPaint.h"
void SampleRender::draw(SkCanvas *canvas, int elapsed, int w, int h) 
{
    m_rotateAngle = int(elapsed * m_rotateSpeed + m_rotateAngle) % 360;
    SkPaint p;
    p.setAntiAlias(true);
    p.setColor(SK_ColorRED);
    p.setStrokeWidth(2.0f);
    canvas->clear(SK_ColorWHITE);
    SkFont font;
    font.setSize(30);
    canvas->rotate(m_rotateAngle, w / 2, h /2);
    canvas->drawString("Hello Skia", w / 2 - 20, h  /2, font, p);
    canvas->drawLine(w * 0.2f, h * 0.2f, w * 0.4f, h * 0.4f, p);
    canvas->flush();
}
