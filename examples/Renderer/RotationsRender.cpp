#include "RotationsRender.h"

#include "core/SkFont.h"
#include "core/SkCanvas.h"
#include "core/SkPaint.h"
void RotationsRender::draw(SkCanvas *canvas, int elapsed, int w, int h)
{
    canvas->translate(128, 0);
    canvas->rotate(60);
    SkRect rect = SkRect::MakeXYWH(0, 0, 200, 100);

    SkPaint paint;
    paint.setAntiAlias(true);
    paint.setColor(0xff4285F4);
    canvas->drawRect(rect, paint);

    canvas->rotate(SkIntToScalar(20));
    paint.setColor(0xffDB4437);
    canvas->drawRect(rect, paint);
    canvas->flush();
}
