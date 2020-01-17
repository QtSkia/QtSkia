#include "BezierRender.h"

void BezierRender::draw(SkCanvas* canvas, int elapsed, int w, int h)
{
    canvas->drawColor(SK_ColorWHITE);
    canvas->drawPath(path, paint);
    canvas->flush();
}

void BezierRender::init(int w, int h)
{
    paint.setStyle(SkPaint::kStroke_Style);
    paint.setStrokeWidth(8);
    paint.setColor(0xff4285F4);
    paint.setAntiAlias(true);
    paint.setStrokeCap(SkPaint::kRound_Cap);

    path.moveTo(10, 10);
    path.quadTo(256, 64, 128, 128);
    path.quadTo(10, 192, 250, 250);
}

void BezierRender::resize(int w, int h)
{
}
